#include <smisc/totalfiniteorder.hpp>

#include <boost/utility.hpp>
#include <ostream>
#include <set>

namespace smisc
{
    boost::optional<TotalFiniteOrder> tfoFromVector
        ( const std::vector<size_t> & v
        )
    {
        // I need to ensure v meets the invariant requirement for
        // TotalFiniteOrder::impl;
        std::set< size_t > set;

        for( const size_t i : v )
            if( i > v.size() )
                return boost::none;
            else
            {
                const auto p = set.insert( i );
                if( !p.second )
                    return boost::none;
            }
        return TotalFiniteOrder( v );
    }
    bool tfoHasRelation
        ( const TotalFiniteOrder & tfo
        , const size_t i
        , const size_t j
        )
    {
        assert( i < tfo.impl.size() );
        assert( j < tfo.impl.size() );
        return
            std::find
              ( tfo.impl.begin()
              , tfo.impl.end()
              , i
              )
          < std::find
              ( tfo.impl.begin()
              , tfo.impl.end()
              , j
              );
    }
    size_t tfoCount( const TotalFiniteOrder & tfo, const size_t i )
    {
        return std::find
              ( tfo.impl.begin()
              , tfo.impl.end()
              , i
              )
            - tfo.impl.begin()
              ;
    }
    size_t tfoAtCount( const TotalFiniteOrder & tfo, const size_t i )
    {
        return tfo.impl[i];
    }
    TotalFiniteOrder tfoAddSmallest( const TotalFiniteOrder & tfo )
    {
        std::vector<size_t> newOrderImpl( tfo.impl.size() + 1 );
        newOrderImpl.front() = 0;
        std::copy
            ( tfo.impl.begin()
            , tfo.impl.end()
            , boost::next
                ( newOrderImpl.begin()
                )
            );
        std::for_each
            ( boost::next( newOrderImpl.begin() )
            , newOrderImpl.end()
            , []( size_t & i ){ ++i; }
            );
        return TotalFiniteOrder( newOrderImpl );
    }
    bool tfoIsTrivial( const TotalFiniteOrder & tfo )
    {
        for( size_t i = 0; i < tfo.impl.size(); ++i )
            if( tfo.impl[i] != i )
                return false;
        return true;
    }
    std::ostream & operator<<( std::ostream & oss, const TotalFiniteOrder & tfo )
    {
        for( const auto & i : tfo.impl )
            oss << i << ' ';
        return oss;
    }
}
#include <boost/test/unit_test.hpp>
#include <boost/assign/list_of.hpp>

BOOST_AUTO_TEST_CASE( tfoSorted_test )
{
    using namespace smisc;
    const std::vector< std::string > v = boost::assign::list_of
        ( std::string( "a" ) )
        ( "b" )
        ( "c" )
        ;
    const TotalFiniteOrder tfo = *tfoFromVector
             ( boost::assign::list_of
                 ( size_t(1) )
                 ( size_t(2) )
                 ( size_t(0) )
             );
    const std::vector< std::string > expectedResult
        = boost::assign::list_of
            ( std::string( "b" ) )
            ( "c" )
            ( "a" );
    const std::vector< std::string > actualResult = tfoSorted( tfo, v );
    BOOST_CHECK_EQUAL_COLLECTIONS( expectedResult.begin(), expectedResult.end(), actualResult.begin(), actualResult.end() );
}
