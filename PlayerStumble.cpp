/*************************************************************************
Crytek Source File.
Copyright (C), Crytek Studios, 2001-2010.

-------------------------------------------------------------------------
History:
- 21:07:2010  Created by Jens Sch?bel

*************************************************************************/

#include "StdAfx.h"
#include "PlayerStumble.h"

using namespace PlayerActor::Stumble;

//////////////////////////////////////////////////////////////////////////
CPlayerStumble::CPlayerStumble()
: m_currentPastTime(-100.f), m_finalActionImpulse(ZERO)
{}

//////////////////////////////////////////////////////////////////////////
void CPlayerStumble::Disable()
{
  m_currentPastTime = -100.f;
}

//////////////////////////////////////////////////////////////////////////
bool CPlayerStumble::Update(float deltaTime, const pe_status_dynamics &dynamics)
{
  if ( m_currentPastTime < -1.f )
    return false;

  m_currentPastTime += deltaTime;

  if ( m_currentPastTime > m_stumbleParameter.periodicTime )
  {
    m_currentPastTime -= m_stumbleParameter.periodicTime;
    m_currentPeriodicScaleX = 1 - Random(0,m_stumbleParameter.randomness );
    m_currentPeriodicScaleY = 1 - Random(0,m_stumbleParameter.randomness );
  }
  m_finalActionImpulse = -(Random(m_stumbleParameter.minDamping, m_stumbleParameter.maxDamping)) * dynamics.v;

  Vec3 stumblingImpulseDir;
  stumblingImpulseDir.x = cosf( m_currentPastTime / m_stumbleParameter.periodicTime * gf_PI2 ) * m_currentPeriodicScaleX * m_stumbleParameter.strengthX;
  stumblingImpulseDir.y = cosf( m_currentPastTime / m_stumbleParameter.periodicTime * gf_PI2 ) * m_currentPeriodicScaleY * m_stumbleParameter.strengthY;
  stumblingImpulseDir.z = 0;
  m_finalActionImpulse += stumblingImpulseDir;

  return true;
}

//////////////////////////////////////////////////////////////////////////
void CPlayerStumble::Start(StumbleParameters* stumbleParameters)
{

  m_currentPastTime = 0;

  m_stumbleParameter.maxDamping = clamp(stumbleParameters->maxDamping, 0, 10000);
  m_stumbleParameter.minDamping = clamp(stumbleParameters->minDamping, 0, 10000);

  if ( m_stumbleParameter.minDamping > m_stumbleParameter.maxDamping )
  {
    float fTemp = m_stumbleParameter.minDamping;
    m_stumbleParameter.minDamping = m_stumbleParameter.maxDamping;
    m_stumbleParameter.maxDamping = fTemp;
  }

  m_stumbleParameter.randomness   = clamp(stumbleParameters->randomness, 0, 2);
  m_stumbleParameter.periodicTime = stumbleParameters->periodicTime;
  m_stumbleParameter.strengthX    = stumbleParameters->strengthX;
  m_stumbleParameter.strengthY    = stumbleParameters->strengthY;

  m_currentPeriodicScaleX = 1 - Random(0,stumbleParameters->randomness );
  m_currentPeriodicScaleY = 1 - Random(0,stumbleParameters->randomness );
}
