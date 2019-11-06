#ifndef MAKE_UNORDERED_MAP_H
#define MAKE_UNORDERED_MAP_H
#include <type_traits>
#include <unordered_map>

namespace details
{
	template <typename T1, typename T2, typename... Args>
	struct map_types
	{
		using TPair = std::pair<T1, T2>;
		using TKey = T1;
		using TValue = T2;
	};

	template <typename... Args>
	struct map_types<void, void, Args...>
	{
		using TPair = typename std::common_type<Args...>::type;
		using TKey = typename std::tuple_element<0, TPair>::type;
		using TValue = typename std::tuple_element<1, TPair>::type;
	};
}

template <typename TKey = void, typename TValue = void, typename... Args>
std::unordered_map<
	typename details::map_types<TKey, TValue, Args...>::TKey,
	typename details::map_types<TKey, TValue, Args...>::TValue> make_unordered_map(Args&&... args)
{
	static_assert((std::is_convertible_v<Args, typename details::map_types<TKey, TValue, Args...>::TPair> &&...),
		"All arguments must be implicitly convertible to std::pair<TKey, TValue>");

	std::unordered_map<
		typename details::map_types<TKey, TValue, Args...>::TKey,
		typename details::map_types<TKey, TValue, Args...>::TValue> map;

	map.reserve(sizeof...(Args));
	(map.emplace(std::forward<Args>(args)), ...);
	return map;
}

#endif
