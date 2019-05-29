#ifndef SIXTRACKLIB_COMMON_BE_LIMIT_CXX_HPP__
#define SIXTRACKLIB_COMMON_BE_LIMIT_CXX_HPP__

#if defined( __cplusplus )

#if !defined( SIXTRL_NO_SYSTEM_INCLUDES )
    #include <cstddef>
    #include <cstdlib>
    #include <type_traits>
    #include <utility>
#endif /* !defined( SIXTRL_NO_SYSTEM_INCLUDES ) */

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/definitions.h"
    #include "sixtracklib/common/buffer.hpp"
    #include "sixtracklib/common/be_limit/be_limit.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

namespace SIXTRL_CXX_NAMESPACE
{
    SIXTRL_STATIC_VAR SIXTRL_CONSTEXPR_OR_CONST NS(particle_real_t)
        BE_LIMIT_DEFAULT_X_LIMIT = static_cast< ::NS(particle_real_t) >(
            SIXTRL_DEFAULT_X_LIMIT );

    SIXTRL_STATIC_VAR SIXTRL_CONSTEXPR_OR_CONST NS(particle_real_t)
        BE_LIMIT_DEFAULT_Y_LIMIT = static_cast< ::NS(particle_real_t) >(
            SIXTRL_DEFAULT_Y_LIMIT );

    template< typename T >
    struct TLimit
    {
        using value_type      = T;
        using reference       = T&;
        using const_reference = T const&;
        using type_id_t       = ::NS(object_type_id_t);
        using buffer_t        = SIXTRL_CXX_NAMESPACE::Buffer;
        using size_type       = buffer_t::size_type;
        using c_buffer_t      = buffer_t::c_api_t;

        static SIXTRL_CONSTEXPR_OR_CONST value_type
            DEFAULT_X_LIMIT = static_cast< value_type >(
                SIXTRL_DEFAULT_X_LIMIT );

        static SIXTRL_CONSTEXPR_OR_CONST value_type
            DEFAULT_Y_LIMIT = static_cast< value_type >(
                SIXTRL_DEFAULT_Y_LIMIT );

        SIXTRL_FN TLimit() = default;

        SIXTRL_FN TLimit( TLimit< T > const& other ) = default;
        TLimit( TLimit< T >&& other ) = default;

        SIXTRL_FN TLimit< T >& operator=( TLimit< T > const& other ) = default;
        SIXTRL_FN TLimit< T >& operator=( TLimit< T >&& other ) = default;

        SIXTRL_FN ~TLimit() = default;

        /* ---------------------------------------------------------------- */

        SIXTRL_STATIC SIXTRL_FN bool CanAddToBuffer(
            buffer_t& SIXTRL_RESTRICT_REF buffer,
            SIXTRL_ARGPTR_DEC size_type* SIXTRL_RESTRICT
                ptr_requ_objects  = nullptr,
            SIXTRL_ARGPTR_DEC size_type* SIXTRL_RESTRICT
                ptr_requ_slots    = nullptr,
            SIXTRL_ARGPTR_DEC size_type* SIXTRL_RESTRICT
                ptr_requ_dataptrs = nullptr ) SIXTRL_NOEXCEPT;

        SIXTRL_STATIC SIXTRL_FN bool CanAddToBuffer(
            SIXTRL_BUFFER_ARGPTR_DEC c_buffer_t* SIXTRL_RESTRICT ptr_buffer,
            SIXTRL_ARGPTR_DEC size_type* SIXTRL_RESTRICT
                ptr_requ_objects  = nullptr,
            SIXTRL_ARGPTR_DEC size_type* SIXTRL_RESTRICT
                ptr_requ_slots    = nullptr,
            SIXTRL_ARGPTR_DEC size_type* SIXTRL_RESTRICT
                ptr_requ_dataptrs = nullptr ) SIXTRL_NOEXCEPT;


        SIXTRL_STATIC SIXTRL_FN SIXTRL_ARGPTR_DEC TLimit< T >*
        CreateNewOnBuffer( buffer_t& SIXTRL_RESTRICT_REF buffer );

        SIXTRL_STATIC SIXTRL_FN SIXTRL_ARGPTR_DEC TLimit< T >*
        CreateNewOnBuffer(
            SIXTRL_BUFFER_ARGPTR_DEC c_buffer_t* SIXTRL_RESTRICT ptr_buffer );



        SIXTRL_STATIC SIXTRL_FN SIXTRL_ARGPTR_DEC TLimit< T >* AddToBuffer(
            buffer_t& SIXTRL_RESTRICT_REF buffer,
            value_type const& dx, value_type const& dy );

        SIXTRL_STATIC SIXTRL_FN SIXTRL_ARGPTR_DEC TLimit< T >* AddToBuffer(
            SIXTRL_BUFFER_ARGPTR_DEC c_buffer_t* SIXTRL_RESTRICT ptr_buffer,
            value_type const& dx, value_type const& dy );

        /* ---------------------------------------------------------------- */

        SIXTRL_FN type_id_t getTypeId() const SIXTRL_NOEXCEPT;

        SIXTRL_STATIC SIXTRL_FN size_type RequiredNumDataPtrs(
            buffer_t const& SIXTRL_RESTRICT_REF buffer ) SIXTRL_NOEXCEPT;

        SIXTRL_STATIC SIXTRL_FN size_type RequiredNumDataPtrs(
            SIXTRL_BUFFER_ARGPTR_DEC const c_buffer_t *const 
                SIXTRL_RESTRICT ptr_buffer ) SIXTRL_NOEXCEPT;
            
        SIXTRL_FN value_type const& getXLimit() const SIXTRL_NOEXCEPT;
        SIXTRL_FN value_type const& getYLimit() const SIXTRL_NOEXCEPT;

        SIXTRL_FN void preset() SIXTRL_NOEXCEPT;

        SIXTRL_FN void setXLimit(
            value_type const& SIXTRL_RESTRICT_REF x_limit ) SIXTRL_NOEXCEPT;

        SIXTRL_FN void setYLimit(
            value_type const& SIXTRL_RESTRICT_REF y_limit ) SIXTRL_NOEXCEPT;

        /* ----------------------------------------------------------------- */

        value_type x_limit SIXTRL_ALIGN( 8 );
        value_type y_limit SIXTRL_ALIGN( 8 );
    };

    template< typename T > struct ObjectTypeTraits<
        SIXTRL_CXX_NAMESPACE::TLimit< T > >
    {
        SIXTRL_STATIC SIXTRL_INLINE object_type_id_t Type() SIXTRL_NOEXCEPT
        {
            return ::NS(OBJECT_TYPE_LIMIT);
        }
    };

    template< typename T >
    SIXTRL_ARGPTR_DEC TLimit< T >* TLimit_new(
        typename TLimit< T >::buffer_t& SIXTRL_RESTRICT_REF buffer );

    template< typename T >
    SIXTRL_ARGPTR_DEC TLimit< T >* TLimit_new(
        SIXTRL_BUFFER_ARGPTR_DEC typename TLimit< T >::c_buffer_t*
            SIXTRL_RESTRICT ptr_buffer );


    template< typename T >
    SIXTRL_ARGPTR_DEC TLimit< T >* TLimit_add(
        typename TLimit< T >::buffer_t& SIXTRL_RESTRICT_REF buffer,
        typename TLimit< T >::value_type const& SIXTRL_RESTRICT_REF x_limits,
        typename TLimit< T >::value_type const& SIXTRL_RESTRICT_REF y_limits );

    template< typename T >
    SIXTRL_ARGPTR_DEC TLimit< T >* TLimit_add(
        SIXTRL_BUFFER_ARGPTR_DEC typename TLimit< T >::c_buffer_t*
            SIXTRL_RESTRICT ptr_buffer,
        typename TLimit< T >::value_type const& SIXTRL_RESTRICT_REF x_limits,
        typename TLimit< T >::value_type const& SIXTRL_RESTRICT_REF y_limits );

    template< typename T >
    SIXTRL_ARGPTR_DEC TLimit< T >* TLimit_add_copy(
        typename TLimit< T >::buffer_t& SIXTRL_RESTRICT_REF buffer,
        TLimit< T > const& SIXTRL_RESTRICT_REF other );

    template< typename T >
    SIXTRL_ARGPTR_DEC TLimit< T >* TLimit_add_copy(
        SIXTRL_BUFFER_ARGPTR_DEC typename TLimit< T >::c_buffer_t*
            SIXTRL_RESTRICT_REF ptr_buffer,
        TLimit< T > const& SIXTRL_RESTRICT_REF other );

    /* ===================================================================== *
     * ====  Specialization TLimit< NS(particle_real_t) > :
     * ===================================================================== */

    template<> struct TLimit< NS(particle_real_t) > : public ::NS(Limit)
    {
        using value_type = ::NS(particle_real_t);
        using type_id_t  = ::NS(object_type_id_t);
        using size_type  = ::NS(buffer_size_t);
        using buffer_t   = SIXTRL_CXX_NAMESPACE::Buffer;
        using c_buffer_t = buffer_t::c_api_t;
        using c_api_t    = ::NS(Limit);

        static SIXTRL_CONSTEXPR_OR_CONST value_type
            DEFAULT_X_LIMIT = static_cast< value_type >(
                SIXTRL_DEFAULT_X_LIMIT );

        static SIXTRL_CONSTEXPR_OR_CONST value_type
            DEFAULT_Y_LIMIT = static_cast< value_type >(
                SIXTRL_DEFAULT_Y_LIMIT );

        SIXTRL_FN TLimit() = default;

        SIXTRL_FN TLimit( TLimit< value_type > const& other ) = default;
        TLimit( TLimit< value_type >&& other ) = default;

        SIXTRL_FN TLimit< value_type >& operator=(
            TLimit< value_type > const& other ) = default;

        SIXTRL_FN TLimit< value_type >& operator=(
            TLimit< value_type >&& other ) = default;

        SIXTRL_FN ~TLimit() = default;

        /* ---------------------------------------------------------------- */

        SIXTRL_STATIC SIXTRL_FN bool CanAddToBuffer(
            buffer_t const& SIXTRL_RESTRICT_REF buffer,
            SIXTRL_ARGPTR_DEC size_type* SIXTRL_RESTRICT
                ptr_requ_objects  = nullptr,
            SIXTRL_ARGPTR_DEC size_type* SIXTRL_RESTRICT
                ptr_requ_slots    = nullptr,
            SIXTRL_ARGPTR_DEC size_type* SIXTRL_RESTRICT
                ptr_requ_dataptrs = nullptr ) SIXTRL_NOEXCEPT;

        SIXTRL_STATIC SIXTRL_FN bool CanAddToBuffer(
            SIXTRL_BUFFER_ARGPTR_DEC const c_buffer_t *const
                SIXTRL_RESTRICT ptr_buffer,
            SIXTRL_ARGPTR_DEC size_type* SIXTRL_RESTRICT
                ptr_requ_objects  = nullptr,
            SIXTRL_ARGPTR_DEC size_type* SIXTRL_RESTRICT
                ptr_requ_slots    = nullptr,
            SIXTRL_ARGPTR_DEC size_type* SIXTRL_RESTRICT
                ptr_requ_dataptrs = nullptr ) SIXTRL_NOEXCEPT;


        SIXTRL_STATIC SIXTRL_FN
        SIXTRL_ARGPTR_DEC TLimit< ::NS(particle_real_t) >*
        CreateNewOnBuffer( buffer_t& SIXTRL_RESTRICT_REF buffer );

        SIXTRL_STATIC SIXTRL_FN
        SIXTRL_ARGPTR_DEC TLimit< ::NS(particle_real_t) >*
        CreateNewOnBuffer( SIXTRL_BUFFER_ARGPTR_DEC c_buffer_t*
            SIXTRL_RESTRICT ptr_buffer );


        SIXTRL_STATIC SIXTRL_FN
        SIXTRL_ARGPTR_DEC TLimit< ::NS(particle_real_t) >* AddToBuffer(
            buffer_t& SIXTRL_RESTRICT_REF buffer,
            value_type const x_limit, value_type const y_limit );

        SIXTRL_STATIC SIXTRL_FN
        SIXTRL_ARGPTR_DEC TLimit< ::NS(particle_real_t) >* AddToBuffer(
            SIXTRL_BUFFER_ARGPTR_DEC c_buffer_t* SIXTRL_RESTRICT ptr_buffer,
            value_type const x_limit, value_type const y_limit );

        /* ----------------------------------------------------------------- */

        SIXTRL_ARGPTR_DEC c_api_t const* getCApiPtr() const SIXTRL_NOEXCEPT;
        SIXTRL_ARGPTR_DEC c_api_t* getCApiPtr() SIXTRL_NOEXCEPT;

        /* ----------------------------------------------------------------- */

        SIXTRL_STATIC SIXTRL_FN size_type RequiredNumDataPtrs(
            buffer_t const& SIXTRL_RESTRICT_REF buffer ) SIXTRL_NOEXCEPT;

        SIXTRL_STATIC SIXTRL_FN size_type RequiredNumDataPtrs(
            SIXTRL_BUFFER_ARGPTR_DEC const c_buffer_t *const
                SIXTRL_RESTRICT ptr_buffer ) SIXTRL_NOEXCEPT;

        SIXTRL_FN type_id_t getTypeId() const SIXTRL_NOEXCEPT;

        SIXTRL_FN value_type getXLimit() const SIXTRL_NOEXCEPT;
        SIXTRL_FN value_type getYLimit() const SIXTRL_NOEXCEPT;

        SIXTRL_FN void preset() SIXTRL_NOEXCEPT;
        SIXTRL_FN void setXLimit( value_type const x_limit ) SIXTRL_NOEXCEPT;
        SIXTRL_FN void setyLimit( value_type const y_limit ) SIXTRL_NOEXCEPT;

    };

    using Limit = TLimit< ::NS(particle_real_t) >;

    SIXTRL_ARGPTR_DEC Limit* Limit_new( SIXTRL_CXX_NAMESPACE::Buffer& buffer );

    SIXTRL_ARGPTR_DEC Limit* Limit_new(
        SIXTRL_ARGPTR_DEC ::NS(Buffer)* SIXTRL_RESTRICT ptr_buffer );

    SIXTRL_ARGPTR_DEC Limit* Limit_add( SIXTRL_CXX_NAMESPACE::Buffer& buffer,
        ::NS(particle_real_t) const x_limit,
        ::NS(particle_real_t) const y_limit );

    SIXTRL_ARGPTR_DEC Limit* Limit_add(
        SIXTRL_BUFFER_ARGPTR_DEC ::NS(Buffer)* SIXTRL_RESTRICT ptr_buffer,
        ::NS(particle_real_t) const x_limit,
        ::NS(particle_real_t) const y_limit );

    SIXTRL_ARGPTR_DEC Limit* Limit_add_copy( 
        SIXTRL_CXX_NAMESPACE::Buffer& buffer,
        SIXTRL_CXX_NAMESPACE::Limit const& SIXTRL_RESTRICT_REF limit );

    SIXTRL_ARGPTR_DEC Limit* Limit_add_copy(
        SIXTRL_ARGPTR_DEC ::NS(Buffer)* SIXTRL_RESTRICT ptr_buffer,
        SIXTRL_CXX_NAMESPACE::Limit const& SIXTRL_RESTRICT_REF limit );
}

/* ************************************************************************* *
 * *** Implementation of inline and template member functions          ***** *
 * ************************************************************************* */


namespace SIXTRL_CXX_NAMESPACE
{
    /* ===================================================================== *
     * ====  TLimit< T > :
     * ===================================================================== */

    template< typename T >
    bool TLimit< T >::CanAddToBuffer(
        typename TLimit< T >::buffer_t& SIXTRL_RESTRICT_REF buffer,
        SIXTRL_ARGPTR_DEC typename TLimit< T >::size_type*
            SIXTRL_RESTRICT req_objects,
        SIXTRL_ARGPTR_DEC typename TLimit< T >::size_type*
            SIXTRL_RESTRICT req_slots,
        SIXTRL_ARGPTR_DEC typename TLimit< T >::size_type*
            SIXTRL_RESTRICT req_dataptrs ) SIXTRL_NOEXCEPT
    {
        return TLimit< T >::CanAddToBuffer(
            buffer.getCApiPtr(), req_objects, req_slots, req_dataptrs );
    }

    template< typename T >
    bool TLimit< T >::CanAddToBuffer(
        SIXTRL_BUFFER_ARGPTR_DEC typename TLimit< T >::c_buffer_t*
            SIXTRL_RESTRICT ptr_buffer,
        SIXTRL_ARGPTR_DEC typename TLimit< T >::size_type*
            SIXTRL_RESTRICT req_objects,
        SIXTRL_ARGPTR_DEC typename TLimit< T >::size_type*
            SIXTRL_RESTRICT req_slots,
        SIXTRL_ARGPTR_DEC typename TLimit< T >::size_type*
            SIXTRL_RESTRICT req_dataptrs ) SIXTRL_NOEXCEPT
    {
        using _this_t = SIXTRL_CXX_NAMESPACE::TLimit< T >;
        using  size_t = typename _this_t::size_type;

        static_assert( std::is_trivial< _this_t >::value, "" );
        static_assert( std::is_standard_layout< _this_t >::value, "" );

        size_t const num_dataptrs = _this_t::RequiredNumDataPtrs( ptr_buffer );
        SIXTRL_ASSERT( num_dataptrs == size_t{ 0 } );

        SIXTRL_ARGPTR_DEC size_t const* sizes  = nullptr;
        SIXTRL_ARGPTR_DEC size_t const* counts = nullptr;

        return ::NS(Buffer_can_add_object)( ptr_buffer, sizeof( _this_t ),
            num_dataptrs, sizes, counts, req_objects, req_slots, req_dataptrs );
    }

    template< typename T >
    SIXTRL_INLINE SIXTRL_ARGPTR_DEC TLimit< T >* TLimit< T >::CreateNewOnBuffer(
        typename TLimit< T >::buffer_t& SIXTRL_RESTRICT_REF buffer )
    {
        return TLimit< T >::CreateNewOnBuffer( buffer.getCApiPtr() );
    }

    template< typename T >
    SIXTRL_INLINE SIXTRL_ARGPTR_DEC TLimit< T >* TLimit< T >::CreateNewOnBuffer(
        SIXTRL_BUFFER_ARGPTR_DEC typename TLimit< T >::c_buffer_t*
            SIXTRL_RESTRICT ptr_buffer )
    {
        using _this_t = SIXTRL_CXX_NAMESPACE::TLimit< T >;
        using size_t  = typename _this_t::size_type;
        using ptr_t   = SIXTRL_ARGPTR_DEC _this_t*;

        static_assert( std::is_trivial< _this_t >::value, "" );
        static_assert( std::is_standard_layout< _this_t >::value, "" );

        size_t const num_dataptrs = _this_t::RequiredNumDataPtrs( ptr_buffer );
        SIXTRL_ASSERT( num_dataptrs == size_t{ 0 } );

        SIXTRL_ARGPTR_DEC size_t const* offsets = nullptr;
        SIXTRL_ARGPTR_DEC size_t const* sizes   = nullptr;
        SIXTRL_ARGPTR_DEC size_t const* counts  = nullptr;

        _this_t temp;
        temp.preset();

        return reinterpret_cast< ptr_t >( ::NS(Object_get_begin_addr)(
            ::NS(Buffer_add_object)( ptr_buffer, &temp, sizeof( _this_t ),
                temp.getTypeId(), num_dataptrs, offsets, sizes, counts ) ) );
    }

    template< typename T >
    SIXTRL_INLINE SIXTRL_ARGPTR_DEC TLimit< T >* TLimit< T >::AddToBuffer(
        typename TLimit< T >::buffer_t& SIXTRL_RESTRICT_REF buffer,
        typename TLimit< T >::value_type const& SIXTRL_RESTRICT_REF x_limit,
        typename TLimit< T >::value_type const& SIXTRL_RESTRICT_REF y_limit )
    {
        return TLimit< T> ::AddToBuffer(
            buffer.getCApiPtr(), x_limit, y_limit );
    }

    template< typename T >
    SIXTRL_INLINE SIXTRL_ARGPTR_DEC TLimit< T >* TLimit< T >::AddToBuffer(
        SIXTRL_BUFFER_ARGPTR_DEC typename TLimit< T >::c_buffer_t*
            SIXTRL_RESTRICT ptr_buffer,
        typename TLimit< T >::value_type const& SIXTRL_RESTRICT_REF x_limit,
        typename TLimit< T >::value_type const& SIXTRL_RESTRICT_REF y_limit )
    {
        using _this_t = SIXTRL_CXX_NAMESPACE::TLimit< T >;
        using size_t  = typename _this_t::size_type;
        using ptr_t   = SIXTRL_ARGPTR_DEC _this_t*;

        static_assert( std::is_trivial< _this_t >::value, "" );
        static_assert( std::is_standard_layout< _this_t >::value, "" );

        size_t const num_dataptrs = _this_t::RequiredNumDataPtrs( ptr_buffer );
        SIXTRL_ASSERT( num_dataptrs == size_t{ 0 } );

        SIXTRL_ARGPTR_DEC size_t const* offsets = nullptr;
        SIXTRL_ARGPTR_DEC size_t const* sizes   = nullptr;
        SIXTRL_ARGPTR_DEC size_t const* counts  = nullptr;

        _this_t temp;
        temp.setXLimit( x_limit );
        temp.setYLimit( y_limit );

        return reinterpret_cast< ptr_t >( ::NS(Object_get_begin_addr)(
            ::NS(Buffer_add_object)( ptr_buffer, &temp, sizeof( _this_t ),
                temp.getTypeId(), num_dataptrs, offsets, sizes, counts ) ) );
    }

    /* ---------------------------------------------------------------- */

    template< typename T >
    SIXTRL_INLINE typename TLimit< T >::type_id_t
    TLimit< T >::getTypeId() const SIXTRL_NOEXCEPT
    {
        return SIXTRL_CXX_NAMESPACE::OBJECT_TYPE_LIMIT;
    }

    template< typename T >
    SIXTRL_INLINE typename TLimit< T >::size_type
    TLimit< T >::RequiredNumDataPtrs( typename TLimit< T >::buffer_t const&
        SIXTRL_RESTRICT_REF buffer ) SIXTRL_NOEXCEPT
    {
        return ::NS(Limit_get_required_num_dataptrs)( 
            buffer.getCApiPtr(), nullptr );
    }
    
    template< typename T >
    SIXTRL_INLINE typename TLimit< T >::size_type 
    TLimit< T >::RequiredNumDataPtrs( 
        SIXTRL_BUFFER_ARGPTR_DEC const typename TLimit< T >::c_buffer_t *const
            SIXTRL_RESTRICT ptr_buffer ) SIXTRL_NOEXCEPT
    {
        return ::NS(Limit_get_required_num_dataptrs)( ptr_buffer, nullptr );
    }

    template< typename T >
    typename TLimit< T >::value_type const&
    TLimit< T >::getXLimit() const SIXTRL_NOEXCEPT
    {
        return this->x_limit;
    }

    template< typename T >
    typename TLimit< T >::value_type const&
    TLimit< T >::getYLimit() const SIXTRL_NOEXCEPT
    {
        return this->y_limit;
    }

    template< typename T >
    void TLimit< T >::preset() SIXTRL_NOEXCEPT
    {
        this->x_limit = SIXTRL_CXX_NAMESPACE::TLimit< T >::DEFAULT_X_LIMIT;
        this->y_limit = SIXTRL_CXX_NAMESPACE::TLimit< T >::DEFAULT_Y_LIMIT;
    }

    template< typename T >
    void TLimit< T >::setXLimit( typename TLimit< T >::value_type const&
        SIXTRL_RESTRICT_REF x_limit ) SIXTRL_NOEXCEPT
    {
        this->x_limit = x_limit;
    }

    template< typename T >
    void TLimit< T >::setYLimit( typename TLimit< T >::value_type const&
            SIXTRL_RESTRICT_REF y_limit ) SIXTRL_NOEXCEPT
    {
        this->y_limit = y_limit;
    }

    /* ----------------------------------------------------------------- */

    template< typename T >
    SIXTRL_ARGPTR_DEC TLimit< T >* TLimit_new(
        typename TLimit< T >::buffer_t& buffer )
    {
        return SIXTRL_CXX_NAMESPACE::TLimit< T >::CreateNewOnBuffer(
            buffer.getCApiPtr() );
    }

    template< typename T >
    SIXTRL_ARGPTR_DEC TLimit< T >* TLimit_new(
        SIXTRL_BUFFER_ARGPTR_DEC typename TLimit< T >::c_buffer_t* ptr_buffer )
    {
        return SIXTRL_CXX_NAMESPACE::TLimit< T >::CreateNewOnBuffer(
            ptr_buffer );
    }

    template< typename T >
    SIXTRL_ARGPTR_DEC TLimit< T >* TLimit_add(
        typename TLimit< T >::buffer_t& SIXTRL_RESTRICT_REF buffer,
        typename TLimit< T >::value_type const& SIXTRL_RESTRICT_REF x_limits,
        typename TLimit< T >::value_type const& SIXTRL_RESTRICT_REF y_limits )
    {
        return SIXTRL_CXX_NAMESPACE::TLimit< T >::AddToBuffer(
            buffer.getCApiPtr(), x_limits, y_limits );
    }

    template< typename T >
    SIXTRL_ARGPTR_DEC TLimit< T >* TLimit_add(
        SIXTRL_BUFFER_ARGPTR_DEC typename TLimit< T >::c_buffer_t*
            SIXTRL_RESTRICT ptr_buffer,
        typename TLimit< T >::value_type const& SIXTRL_RESTRICT_REF x_limits,
        typename TLimit< T >::value_type const& SIXTRL_RESTRICT_REF y_limits )
    {
        return SIXTRL_CXX_NAMESPACE::TLimit< T >::AddToBuffer(
            ptr_buffer, x_limits, y_limits );
    }

    template< typename T >
    SIXTRL_ARGPTR_DEC TLimit< T >* TLimit_add_copy(
        typename TLimit< T >::buffer_t& SIXTRL_RESTRICT_REF buffer,
        TLimit< T > const& SIXTRL_RESTRICT_REF  other )
    {
        return SIXTRL_CXX_NAMESPACE::TLimit< T >::AddToBuffer(
            buffer.getCApiPtr(), other.getXLimit(), other.getYLimit() );
    }

    template< typename T >
    SIXTRL_ARGPTR_DEC TLimit< T >* TLimit_add_copy(
        SIXTRL_BUFFER_ARGPTR_DEC typename TLimit< T >::c_buffer_t*
            SIXTRL_RESTRICT ptr_buffer,
        TLimit< T > const& SIXTRL_RESTRICT_REF  other )
    {
        return SIXTRL_CXX_NAMESPACE::TLimit< T >::AddToBuffer(
            ptr_buffer, other.getXLimit(), other.getYLimit() );
    }

    /* ===================================================================== *
     * ====  Specialization TLimit< ::NS(particle_real_t) > :
     * ===================================================================== */

    template<>
    bool TLimit< ::NS(particle_real_t) >::CanAddToBuffer(
        TLimit< ::NS(particle_real_t) >::buffer_t const& SIXTRL_RESTRICT_REF buffer,
        SIXTRL_ARGPTR_DEC TLimit< ::NS(particle_real_t) >::size_type*
            SIXTRL_RESTRICT ptr_requ_objects,
        SIXTRL_ARGPTR_DEC TLimit< ::NS(particle_real_t) >::size_type*
            SIXTRL_RESTRICT ptr_requ_slots,
        SIXTRL_ARGPTR_DEC TLimit< ::NS(particle_real_t) >::size_type*
            SIXTRL_RESTRICT ptr_requ_dataptrs ) SIXTRL_NOEXCEPT
    {
        return ::NS(Limit_can_be_added)( buffer.getCApiPtr(), ptr_requ_objects,
            ptr_requ_slots, ptr_requ_dataptrs );
    }


    template<>
    bool TLimit< ::NS(particle_real_t) >::CanAddToBuffer(
        SIXTRL_BUFFER_ARGPTR_DEC TLimit< ::NS(particle_real_t) >::c_buffer_t*
            SIXTRL_RESTRICT ptr_buffer,
        SIXTRL_ARGPTR_DEC TLimit< ::NS(particle_real_t) >::size_type*
            SIXTRL_RESTRICT ptr_requ_objects,
        SIXTRL_ARGPTR_DEC TLimit< ::NS(particle_real_t) >::size_type*
            SIXTRL_RESTRICT ptr_requ_slots,
        SIXTRL_ARGPTR_DEC TLimit< ::NS(particle_real_t) >::size_type*
            SIXTRL_RESTRICT ptr_requ_dataptrs ) SIXTRL_NOEXCEPT
    {
        return ::NS(Limit_can_be_added)( buffer.getCApiPtr(), ptr_requ_objects,
            ptr_requ_slots, ptr_requ_dataptrs );
    }

    template<>
    SIXTRL_INLINE SIXTRL_ARGPTR_DEC TLimit< NS(particle_real_t) >*
    TLimit< ::NS(particle_real_t) >::CreateNewOnBuffer(
        TLimit< ::NS(particle_real_t) >::buffer_t& SIXTRL_RESTRICT_REF buffer )
    {
        return ::NS(Limit_new)( buffer.getCApiPtr() );
    }

    template<>
    SIXTRL_INLINE SIXTRL_ARGPTR_DEC TLimit< NS(particle_real_t) >*
    TLimit< ::NS(particle_real_t) >::CreateNewOnBuffer(
        SIXTRL_BUFFER_ARGPTR_DEC TLimit< ::NS(particle_real_t) >::c_buffer_t*
            SIXTRL_RESTRICT ptr_buffer )
    {
        return ::NS(Limit_new)( ptr_buffer );
    }

    template<>
    SIXTRL_ARGPTR_DEC TLimit< NS(particle_real_t) >*
    TLimit< ::NS(particle_real_t) >::AddToBuffer(
        TLimit< ::NS(particle_real_t) >::buffer_t& SIXTRL_RESTRICT_REF buffer,
        TLimit< ::NS(particle_real_t) >::value_type const x_limit,
        TLimit< ::NS(particle_real_t) >::value_type const y_limit )
    {
        return ::NS(Limit_add)( buffer.getCApiPtr(), x_limit, y_limit );
    }

    template<>
    SIXTRL_ARGPTR_DEC TLimit< NS(particle_real_t) >*
    TLimit< ::NS(particle_real_t) >::AddToBuffer(
        SIXTRL_BUFFER_ARGPTR_DEC TLimit< ::NS(particle_real_t) >::c_buffer_t*
            SIXTRL_RESTRICT ptr_buffer,
        TLimit< ::NS(particle_real_t) >::value_type const x_limit,
        TLimit< ::NS(particle_real_t) >::value_type const y_limit )
    {
        return ::NS(Limit_add)( ptr_buffer, x_limit, y_limit );
    }

    /* ----------------------------------------------------------------- */

    template<>
    SIXTRL_ARGPTR_DEC TLimit< ::NS(particle_real_t) >::c_api_t const*
    TLimit< ::NS(particle_real_t) >::getCApiPtr() const SIXTRL_NOEXCEPT
    {
        using ptr_t = TLimit< ::NS(particle_real_t) >::c_api_t const*;
        return reinterpret_cast< ptr_t >( this );
    }

    template<>
    SIXTRL_ARGPTR_DEC TLimit< ::NS(particle_real_t) >::c_api_t*
    TLimit< ::NS(particle_real_t) >::getCApiPtr() SIXTRL_NOEXCEPT
    {
        return const_cast< TLimit< ::NS(particle_real_t) >::c_api_t* >(
            static_cast< TLimit< ::NS(particle_real_t) > const& >( *this
                ).getCApiPtr() );
    }

    /* ----------------------------------------------------------------- */

    template<>
    TLimit< ::NS(particle_real_t) >::type_id_t
    TLimit< ::NS(particle_real_t) >::getTypeId() const SIXTRL_NOEXCEPT
    {
        return SIXTRL_CXX_NAMESPACE::OBJECT_TYPE_LIMIT;
    }

    template<>
    TLimit< ::NS(particle_real_t) >::size_type
    TLimit< ::NS(particle_real_t) >::RequiredNumDataPtrs(
        TLimit< ::NS(particle_real_t) >::buffer_t const&
            SIXTRL_RESTRICT_REF buffer ) SIXTRL_NOEXCEPT
    {
        return ::NS(Limit_get_required_num_dataptrs)( 
            buffer.getCApiPtr(), nullptr );
    }

    template<>
    TLimit< ::NS(particle_real_t) >::size_type
    TLimit< ::NS(particle_real_t) >::RequiredNumDataPtrs(
        SIXTRL_BUFFER_ARGPTR_DEC const
            TLimit< ::NS(particle_real_t) >::c_buffer_t *const
                SIXTRL_RESTRICT ptr_buffer ) SIXTRL_NOEXCEPT
    {
        return ::NS(Limit_get_required_num_dataptrs)( 
            ptr_buffer, nullptr );
    }

    template<>
    TLimit< ::NS(particle_real_t) >::value_type
    TLimit< ::NS(particle_real_t) >::getXLimit() const SIXTRL_NOEXCEPT
    {
        return ::NS(Limit_get_x_limit)( this->getCApiPtr() );
    }

    template<>
    TLimit< ::NS(particle_real_t) >::value_type
    TLimit< ::NS(particle_real_t) >::getYLimit() const SIXTRL_NOEXCEPT
    {
        return ::NS(Limit_get_y_limit)( this->getCApiPtr() );
    }

    template<>
    void TLimit< ::NS(particle_real_t) >::preset() SIXTRL_NOEXCEPT
    {
        ::NS(Limit_preset)( this->getCApiPtr() );
    }

    template<>
    void TLimit< ::NS(particle_real_t) >::setXLimit(
        TLimit< ::NS(particle_real_t) >::value_type
            const x_limit ) SIXTRL_NOEXCEPT
    {
        ::NS(Limit_set_x_limit)( this->getCApiPtr(), x_limit );
    }

    template<>
    void TLimit< ::NS(particle_real_t) >::setyLimit(
        TLimit< ::NS(particle_real_t) >::value_type const
            y_limit ) SIXTRL_NOEXCEPT
    {
        ::NS(Limit_set_y_limit)( this->getCApiPtr(), y_limit );
    }

    SIXTRL_ARGPTR_DEC SIXTRL_CXX_NAMESPACE::Limit* Limit_new(
        SIXTRL_CXX_NAMESPACE::Buffer& SIXTRL_RESTRICT_REF buffer )
    {
        return static_cast< SIXTRL_ARGPTR_DEC Limit* >(
            ::NS(Limit_new)( buffer.getCApiPtr() ) );
    }

    SIXTRL_ARGPTR_DEC SIXTRL_CXX_NAMESPACE::Limit* Limit_new(
        SIXTRL_ARGPTR_DEC ::NS(Buffer)* SIXTRL_RESTRICT ptr_buffer )
    {
        return static_cast< SIXTRL_ARGPTR_DEC Limit* >(
            ::NS(Limit_new)( ptr_buffer ) );
    }

    SIXTRL_ARGPTR_DEC SIXTRL_CXX_NAMESPACE::Limit* Limit_add(
        SIXTRL_CXX_NAMESPACE::Buffer& SIXTRL_RESTRICT_REF buffer,
        NS(particle_real_t) const x_limit, NS(particle_real_t) const y_limit )
    {
        return static_cast< SIXTRL_ARGPTR_DEC Limit* >(
            ::NS(Limit_add)( buffer.getCApiPtr(), x_limit, y_limit );
    }

    SIXTRL_ARGPTR_DEC Limit* Limit_add(
        SIXTRL_ARGPTR_DEC NS(Buffer)* SIXTRL_RESTRICT ptr_buffer,
        NS(particle_real_t) const x_limit, NS(particle_real_t) const y_limit )
    {
        return static_cast< SIXTRL_ARGPTR_DEC Limit* >(
            ::NS(Limit_add)( ptr_buffer, x_limit, y_limit );
    }

    SIXTRL_ARGPTR_DEC SIXTRL_CXX_NAMESPACE::Limit* Limit_add_copy(
        SIXTRL_CXX_NAMESPACE::Buffer& SIXTRL_RESTRICT_REF buffer,
        SIXTRL_CXX_NAMESPACE::Limit const& SIXTRL_RESTRICT_REF other )
    {
        return static_cast< SIXTRL_ARGPTR_DEC Limit* >(
            ::NS(Limit_add_copy)( buffer.getCApiPtr(), other.getCApiPtr() );
    }

    SIXTRL_ARGPTR_DEC SIXTRL_CXX_NAMESPACE::Limit* Limit_add_copy(
        SIXTRL_ARGPTR_DEC NS(Buffer)* SIXTRL_RESTRICT ptr_buffer,
        SIXTRL_CXX_NAMESPACE::Limit const& SIXTRL_RESTRICT_REF other )
    {
        return static_cast< SIXTRL_ARGPTR_DEC SIXTRL_CXX_NAMESPACE::Limit* >(
            ::NS(Limit_add_copy)( ptr_buffer, other.getCApiPtr() );
    }
}

#endif /* __cplusplus */

#endif /* SIXTRACKLIB_COMMON_BE_LIMIT_CXX_HPP__ */

/* end: sixtracklib/common/be_limit/be_limit.hpp */
