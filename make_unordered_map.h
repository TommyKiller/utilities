#ifndef MAKE_UNORDERED_MAP_H
#define MAKE_UNORDERED_MAP_H
#pragma once

// Standard Headers
#include <type_traits>
#include <unordered_map>

// Define Namespace
namespace utils
{
	// Define Namespace
	namespace detail
	{
		template <typename T1, typename T2, typename THash, typename... Args>
		struct map_types
		{
			using TPair = std::pair<T1, T2>;
			using TKey = T1;
			using TValue = T2;
			using THasher = THash;
		};

		template <typename... Args>
		struct map_types<void, void, void, Args...>
		{
			using TPair = typename std::common_type<Args...>::type;
			using TKey = typename std::tuple_element<0, TPair>::type;
			using TValue = typename std::tuple_element<1, TPair>::type;
			using THasher = typename std::hash<TKey>;
		};
	} // namespace detail

	template <typename TKey = void, typename TValue = void, typename Hasher = void, typename... Args>
	std::unordered_map<
		typename detail::map_types<TKey, TValue, Hasher, Args...>::TKey,
		typename detail::map_types<TKey, TValue, Hasher, Args...>::TValue,
		typename detail::map_types<TKey, TValue, Hasher, Args...>::THasher> make_unordered_map(Args&&... args)
	{
		static_assert((std::is_convertible_v<Args, typename detail::map_types<TKey, TValue, Hasher, Args...>::TPair> &&...),
			"All arguments must be implicitly convertible to std::pair<TKey, TValue>");

		std::unordered_map<
			typename detail::map_types<TKey, TValue, Hasher, Args...>::TKey,
			typename detail::map_types<TKey, TValue, Hasher, Args...>::TValue,
			typename detail::map_types<TKey, TValue, Hasher, Args...>::THasher> map;

		map.reserve(sizeof...(Args));
		(map.emplace(std::forward<Args>(args)), ...);
		return map;
	}
} // namespace utils

#endif // MAKE_UNORDERED_MAP_H
