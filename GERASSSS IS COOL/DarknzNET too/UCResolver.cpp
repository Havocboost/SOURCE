#include "Backtracking.h"
#include "sdk.h"
#include "UCResolver.h"

//void CResolver::Resolve( CBaseEntity* ent ) {
//	auto cur = m_arrInfos.at( ent->GetModelIndex() ).m_sRecords;
//	if ( cur.size() < 2 )
//		entity->m_vecAngVelocity().y = cur.front().m_flLowerBodyYawTarget;
//	}
//	else if ( Config->GetValue<int>( "Resolver", "Mode" ) == static_cast<int>( ResolveMode::DELTA ) ) {
//		ent->m_angEyeAngles().y = LBYDelta( cur.front() );
//	}
//	else if ( Config->GetValue<int>( "Resolver", "Mode" ) == static_cast<int>( ResolveMode::STEADY ) ) {
//		if ( cur.size() <= 1 )
//			return;
//		float tickdif = static_cast<float>( cur.front().tickcount - cur.at( 1 ).tickcount );
//		float lbydif = GetDelta( cur.front().m_flLowerBodyYawTarget, cur.at( 1 ).m_flLowerBodyYawTarget );
//		float ntickdif = static_cast<float>( G::UserCmd->tick_count - cur.front().tickcount );
//		ent->m_angEyeAngles().y = ( lbydif / tickdif ) * ntickdif;
//	}
//	else if ( Config->GetValue<int>( "Resolver", "Mode" ) == static_cast<int>( ResolveMode::TICKMODULO ) ) {
//		ent->m_angEyeAngles().y = ent->GetEyeAngles().y - GetDeltaByComparingTicks( cur );
//	}
//	else if ( Config->GetValue<int>( "Resolver", "Mode" ) == static_cast<int>( ResolveMode::ALL ) ) {
//		if ( Backtracking->CanBacktrackShot( GetShotRecord( ent ) ) )
//			m_arrInfos.at( ent->entindex() ).m_sRecords.erase( std::remove( m_arrInfos.at( ent->entindex() ).m_sRecords.begin(), m_arrInfos.at( ent->entindex() ).m_sRecords.end(), GetShotRecord( ent ) ), m_arrInfos.at( ent->entindex() ).m_sRecords.end() );
//		else if ( IsEntityMoving( ent ) )
//			ent->m_angEyeAngles().y = ent->GetLowerBodyYawTarget();
//		else if ( HasStaticRealAngle( cur ) )
//			ent->m_angEyeAngles().y = ( cur.front().m_flLowerBodyYawTarget ) + ( M::RandomFloat( 0.f, 1.f ) > 0.5f ? 10 : -10 );
//		else if ( HasStaticYawDifference( cur ) )
//			ent->m_angEyeAngles().y = ent->GetEyeAngles().y - ( cur.front().m_angEyeAngles.y - cur.front().m_flLowerBodyYawTarget );
//		else if ( HasSteadyDifference( cur ) ) {
//			float tickdif = static_cast<float>( cur.front().tickcount - cur.at( 1 ).tickcount );
//			float lbydif = GetDelta( cur.front().m_flLowerBodyYawTarget, cur.at( 1 ).m_flLowerBodyYawTarget );
//			float ntickdif = static_cast<float>( G::UserCmd->tick_count - cur.front().tickcount );
//			ent->m_angEyeAngles().y = ( lbydif / tickdif ) * ntickdif;
//		}
//		else if ( DeltaKeepsChanging( cur ) )
//			ent->m_angEyeAngles().y = ent->GetEyeAngles().y - GetDeltaByComparingTicks( cur );
//		else if ( LBYKeepsChanging( cur ) )
//			ent->m_angEyeAngles().y = GetLBYByComparingTicks( cur );
//		else
//			ent->m_angEyeAngles().y = ent->GetEyeAngles().y + 180;
//	}
//}

bool CResolver::IsEntityMoving( CBaseEntity* ent ) {
	return ( ent->GetVelocity().Length2D() > 0.1f && ent->GetFlags() & FL_ONGROUND );
}