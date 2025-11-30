#ifndef SET_HPP
# define SET_HPP

# include <__algorithm/equal.h>
# include <__algorithm/lexicographical_compare.h>
# include <__algorithm/lexicographical_compare_three_way.h>
# include <__assert> // all public C++ headers provide the assertion handler
# include <__availability>
# include <__config>
# include <__functional/is_transparent.h>
# include <__functional/operations.h>
# include <__iterator/erase_if_container.h>
# include <__iterator/iterator_traits.h>
# include <__iterator/ranges_iterator_traits.h>
# include <__iterator/reverse_iterator.h>
# include <__memory/allocator.h>
# include <__memory_resource/polymorphic_allocator.h>
# include <__node_handle>
# include <__ranges/concepts.h>
# include <__ranges/container_compatible_range.h>
# include <__ranges/from_range.h>
# include "__tree"
# include <__type_traits/is_allocator.h>
# include <__utility/forward.h>
# include <version>

// standard-mandated includes

// [iterator.range]
# include <__iterator/access.h>
# include <__iterator/data.h>
# include <__iterator/empty.h>
# include <__iterator/reverse_access.h>
# include <__iterator/size.h>

// [associative.set.syn]
# include <compare>
# include <initializer_list>

#if !defined(_LIBCPP_HAS_NO_PRAGMA_SYSTEM_HEADER)
#  pragma GCC system_header
#endif

_LIBCPP_PUSH_MACROS
# include <__undef_macros>

# if !defined(_LIBCPP_HAS_NO_PRAGMA_SYSTEM_HEADER)
#  pragma GCC system_header
# endif

namespace ft {
	template <class _Key, std::size_t M = 4>
	class _LIBCPP_TEMPLATE_VIS set {
		public: // types
			typedef _Key                                     key_type;
			typedef key_type                                 value_type;
			typedef value_type&                              reference;
			typedef const value_type&                        const_reference;

		private:
			typedef __tree<value_type, M>   __base;

		private:
			__base __tree_;

		public:
			typedef typename __base::pointer			pointer;
			typedef typename __base::const_pointer		const_pointer;
			typedef typename __base::size_type			size_type;
			typedef typename __base::difference_type	difference_type;
			typedef typename __base::const_iterator		iterator;
			typedef typename __base::const_iterator		const_iterator;

		_LIBCPP_INLINE_VISIBILITY set(): __tree_() {}

		_LIBCPP_INLINE_VISIBILITY ~set() {}

		_LIBCPP_INLINE_VISIBILITY
		iterator begin() _NOEXCEPT { return __tree_.begin(); }
		_LIBCPP_INLINE_VISIBILITY
		const_iterator begin() const _NOEXCEPT { return __tree_.begin(); }
		_LIBCPP_INLINE_VISIBILITY
		iterator end() _NOEXCEPT { return __tree_.end(); }
		_LIBCPP_INLINE_VISIBILITY
		const_iterator end() const _NOEXCEPT { return __tree_.end(); }

		_LIBCPP_NODISCARD_AFTER_CXX17 _LIBCPP_INLINE_VISIBILITY
		bool empty() const _NOEXCEPT { return __tree_.size() == 0; }
		_LIBCPP_INLINE_VISIBILITY
		size_type size() const _NOEXCEPT { return __tree_.size(); }

		// modifiers:
		_LIBCPP_INLINE_VISIBILITY
		std::pair<iterator, bool> insert(const value_type& __v) { return __tree_.__insert_unique(__v); }
		_LIBCPP_INLINE_VISIBILITY
		size_type erase(const key_type& __k) { return __tree_.__erase_unique(__k); }
		_LIBCPP_INLINE_VISIBILITY
		void clear() _NOEXCEPT { __tree_.clear(); }
		
		// set operations:
		_LIBCPP_INLINE_VISIBILITY
		iterator find(const key_type& __k)             { return __tree_.find(__k); }
		_LIBCPP_INLINE_VISIBILITY
		const_iterator find(const key_type& __k) const { return __tree_.find(__k); }
	
		_LIBCPP_INLINE_VISIBILITY
		size_type      count(const key_type& __k) const { return __tree_.__count_unique(__k); }

	# if _LIBCPP_STD_VER > 17
		_LIBCPP_INLINE_VISIBILITY
		bool contains(const key_type& __k) const { return find(__k) != end(); }
	# endif // _LIBCPP_STD_VER > 17

		_LIBCPP_INLINE_VISIBILITY
		iterator lower_bound(const key_type& __k) { return __tree_.lower_bound(__k); }
		_LIBCPP_INLINE_VISIBILITY
		const_iterator lower_bound(const key_type& __k) const { return __tree_.lower_bound(__k); }

		_LIBCPP_INLINE_VISIBILITY
		iterator upper_bound(const key_type& __k) { return __tree_.upper_bound(__k); }
		_LIBCPP_INLINE_VISIBILITY
		const_iterator upper_bound(const key_type& __k) const { return __tree_.upper_bound(__k); }

		friend std::ostream& operator<<(std::ostream& os, const set& set) {
			os << set.__tree_;
			return os;
		}
	};
}

_LIBCPP_POP_MACROS

# if !defined(_LIBCPP_REMOVE_TRANSITIVE_INCLUDES) && _LIBCPP_STD_VER <= 20
#  include <concepts>
#  include <cstdlib>
#  include <functional>
#  include <iterator>
#  include <stdexcept>
#  include <type_traits>
# endif

#endif // _LIBCPP_SET
