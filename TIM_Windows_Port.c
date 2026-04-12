// #############################################################################
// #### Copyright ##############################################################
// #############################################################################

/*
 * Copyright 2024 BaSSeM
 *
 *    Licensed under the Apache License, Version 2.0 (the "License");
 *    you may not use this file except in compliance with the License.
 *    You may obtain a copy of the License at
 *
 *        http://www.apache.org/licenses/LICENSE-2.0
 *
 *    Unless required by applicable law or agreed to in writing, software
 *    distributed under the License is distributed on an "AS IS" BASIS,
 *    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *    See the License for the specific language governing permissions and
 *    limitations under the License.
 */

// #############################################################################
// #### Description ############################################################
// #############################################################################

// #############################################################################
// #### Control Include(s) #####################################################
// #############################################################################

#include "Platform.h"

// #############################################################################
// #### Control Macro(s) #######################################################
// #############################################################################

#ifndef DEBUG
    #define DEBUG
#endif

#ifdef DEBUG
    #undef DEBUG
#endif

// #############################################################################
// #### File Guard #############################################################
// #############################################################################

#ifdef TIM_WINDOWS

// #############################################################################
// #### Include(s) #############################################################
// #############################################################################

    #include "../../TIM_Internal.h"
    #include "TIM_Windows_Port.h"

// #############################################################################
// #### Private Macro(s) #######################################################
// #############################################################################

// #############################################################################
// #### Private Type(s) ########################################################
// #############################################################################

typedef struct TIM_InstanceContext
{
    TIM_Timestamp_t Timestamp;

    union
    {
        RTC_t RTC;
    };
} TIM_InstanceContext_t;

// #############################################################################
// #### Private Method(s) Prototype ############################################
// #############################################################################

// #############################################################################
// #### Private Variable(s) ####################################################
// #############################################################################

// #############################################################################
// #### Private Method(s) ######################################################
// #############################################################################

// #############################################################################
// #### Public Method(s) #######################################################
// #############################################################################

TIM_Status_t TIM_IsValid( TIM_t TIM )
{
    TIM_Status_t TIM_Status = TIM_Status_Error;
    do
    {
        TIM_Trace( "%s( TIM=%d )", __FUNCTION__, TIM );
        switch ( TIM )
        {
            case TIM_1:
            case TIM_2:
                TIM_Status = TIM_Status_Success;
                break;
            default:
                TIM_Status = TIM_Status_ArgumentInvalid;
                break;
        }
    }
    while ( 0 );
    return TIM_Status;
}

TIM_Status_t TIM_Instance_Initialize( TIM_Instance_t * TIM_Instance )
{
    TIM_Status_t TIM_Status = TIM_Status_Error;
    do
    {
        TIM_Trace( "%s( Instance=%p )", __FUNCTION__, TIM_Instance );
        if ( ( TIM_Status = TIM_Instance_IsValid( TIM_Instance ) ) != TIM_Status_Success )
        {
            break;
        }
        if ( TIM_Instance->Context == NULL )
        {
            RAM_Status_t RAM_Status = RAM_Status_Error;
            if ( ( RAM_Status = RAM_Allocate( RAM_1, ( RAM_Reference_t * ) &TIM_Instance->Context, UTIL_SizeOf( TIM_InstanceContext_t ) ) ) != RAM_Status_Success )
            {
                TIM_Status = TIM_Status_Error;
                break;
            }
            // Double check context validity
            if ( TIM_Instance->Context == NULL )
            {
                TIM_Status = TIM_Status_Error;
                break;
            }
        }
        switch ( TIM_Instance->TIM )
        {
            case TIM_1:
                TIM_Instance->Context->RTC = RTC_1;
                TIM_Status = TIM_Status_Success;
                break;
            case TIM_2:
                TIM_Instance->Context->RTC = RTC_2;
                TIM_Status = TIM_Status_Success;
                break;
            default:
                TIM_Status = TIM_Status_Error;
                break;
        }
        switch ( TIM_Status )
        {
            case TIM_Status_Success:
                do
                {
                    TIM_Instance->Context->Timestamp.Year = TIM_Year_Unknown;
                    TIM_Instance->Context->Timestamp.Month = TIM_Month_Unknown;
                    TIM_Instance->Context->Timestamp.Day = TIM_Day_Unknown;
                    TIM_Instance->Context->Timestamp.Hour = TIM_Hour_Unknown;
                    TIM_Instance->Context->Timestamp.Minute = TIM_Minute_Unknown;
                    TIM_Instance->Context->Timestamp.Second = TIM_Second_Unknown;
                    TIM_Instance->Context->Timestamp.Millisecond = TIM_Millisecond_Unknown;
                    TIM_Instance->Context->Timestamp.Microsecond = TIM_Microsecond_Unknown;
                    TIM_Instance->Context->Timestamp.Weekday = TIM_Weekday_Unknown;
                }
                while ( 0 );
                break;
            default:
                // Nothing to be done
                break;
        }
    }
    while ( 0 );
    return TIM_Status;
}

TIM_Status_t TIM_Instance_Cycle( TIM_Instance_t * TIM_Instance )
{
    TIM_Status_t TIM_Status = TIM_Status_Error;
    do
    {
        TIM_Trace( "%s( Instance=%p )", __FUNCTION__, TIM_Instance );
        if ( ( TIM_Status = TIM_Instance_IsValid( TIM_Instance ) ) != TIM_Status_Success )
        {
            break;
        }
        switch ( TIM_Instance->TIM )
        {
            case TIM_1:
            case TIM_2:
                do
                {
                    RTC_Timestamp_t RTC_Timestamp;
                    RTC_Status_t RTC_Status = RTC_Status_Error;
                    if ( ( RTC_Status = RTC_Get_Timestamp( TIM_Instance->Context->RTC, &RTC_Timestamp ) ) != RTC_Status_Success )
                    {
                        TIM_Status = TIM_Status_Error;
                        break;
                    }
                    TIM_Instance->Context->Timestamp.Year = RTC_Timestamp.Year;
                    TIM_Instance->Context->Timestamp.Month = RTC_Timestamp.Month;
                    TIM_Instance->Context->Timestamp.Day = RTC_Timestamp.Day;
                    TIM_Instance->Context->Timestamp.Hour = RTC_Timestamp.Hour;
                    TIM_Instance->Context->Timestamp.Minute = RTC_Timestamp.Minute;
                    TIM_Instance->Context->Timestamp.Second = RTC_Timestamp.Second;
                    TIM_Instance->Context->Timestamp.Millisecond = RTC_Timestamp.Millisecond;
                    TIM_Instance->Context->Timestamp.Microsecond = RTC_Timestamp.Microsecond;
                    TIM_Instance->Context->Timestamp.Weekday = RTC_Timestamp.Weekday;
                    TIM_Status = TIM_Status_Success;
                }
                while ( 0 );
                break;
            default:
                TIM_Status = TIM_Status_Error;
                break;
        }
    }
    while ( 0 );
    return TIM_Status;
}

TIM_Status_t TIM_Instance_DeInitialize( TIM_Instance_t * TIM_Instance )
{
    TIM_Status_t TIM_Status = TIM_Status_Error;
    do
    {
        TIM_Trace( "%s( Instance=%p )", __FUNCTION__, TIM_Instance );
        if ( ( TIM_Status = TIM_Instance_IsValid( TIM_Instance ) ) != TIM_Status_Success )
        {
            break;
        }
        // Nothing to be done
        TIM_Status = TIM_Status_Success;
    }
    while ( 0 );
    return TIM_Status;
}

TIM_Status_t TIM_Instance_GetTimestamp( TIM_Instance_t * TIM_Instance, TIM_Timestamp_t * TIM_Timestamp )
{
    TIM_Status_t TIM_Status = TIM_Status_Error;
    do
    {
        TIM_Trace( "%s( Instance=%p, Timestamp=%p )", __FUNCTION__, TIM_Instance, TIM_Timestamp );
        if ( TIM_Timestamp == NULL )
        {
            TIM_Status = TIM_Status_ArgumentInvalid;
            break;
        }
        if ( ( TIM_Status = TIM_Instance_IsValid( TIM_Instance ) ) != TIM_Status_Success )
        {
            break;
        }
        switch ( TIM_Instance->TIM )
        {
            case TIM_1:
            case TIM_2:
                if ( TIM_Instance->Context == NULL )
                {
                    TIM_Status = TIM_Status_Error;
                    break;
                }
                *TIM_Timestamp = TIM_Instance->Context->Timestamp;
                TIM_Status = TIM_Status_Success;
                break;
            default:
                TIM_Status = TIM_Status_ArgumentInvalid;
                break;
        }
    }
    while ( 0 );

    return TIM_Status;
}

TIM_Status_t TIM_Instance_IsExpiredTimestamp( TIM_Instance_t * TIM_Instance, TIM_Timestamp_t * TIM_Timestamp )
{
    TIM_Status_t TIM_Status = TIM_Status_Error;
    do
    {
        TIM_Trace( "%s( Instance=%p, Timestamp=%p )", __FUNCTION__, TIM_Instance, TIM_Timestamp );
        if ( TIM_Timestamp == NULL )
        {
            TIM_Status = TIM_Status_ArgumentInvalid;
            break;
        }
        if ( ( TIM_Status = TIM_Instance_IsValid( TIM_Instance ) ) != TIM_Status_Success )
        {
            break;
        }
        if ( TIM_Instance->Context->Timestamp.Year < TIM_Timestamp->Year )
        {
            // Not expired
            TIM_Status = TIM_Status_Error;
            break;
        }
        if ( TIM_Instance->Context->Timestamp.Year > TIM_Timestamp->Year )
        {
            // Expired
            TIM_Status = TIM_Status_Success;
            break;
        }

        if ( TIM_Instance->Context->Timestamp.Month < TIM_Timestamp->Month )
        {
            // Not expired
            TIM_Status = TIM_Status_Error;
            break;
        }

        if ( TIM_Instance->Context->Timestamp.Month > TIM_Timestamp->Month )
        {
            // Expired
            TIM_Status = TIM_Status_Success;
            break;
        }

        if ( TIM_Instance->Context->Timestamp.Day < TIM_Timestamp->Day )
        {
            // Not expired
            TIM_Status = TIM_Status_Error;
            break;
        }

        if ( TIM_Instance->Context->Timestamp.Day > TIM_Timestamp->Day )
        {
            // Expired
            TIM_Status = TIM_Status_Success;
            break;
        }

        if ( TIM_Instance->Context->Timestamp.Hour < TIM_Timestamp->Hour )
        {
            // Not expired
            TIM_Status = TIM_Status_Error;
            break;
        }

        if ( TIM_Instance->Context->Timestamp.Hour > TIM_Timestamp->Hour )
        {
            // Expired
            TIM_Status = TIM_Status_Success;
            break;
        }

        if ( TIM_Instance->Context->Timestamp.Minute < TIM_Timestamp->Minute )
        {
            // Not expired
            TIM_Status = TIM_Status_Error;
            break;
        }

        if ( TIM_Instance->Context->Timestamp.Minute > TIM_Timestamp->Minute )
        {
            // Expired
            TIM_Status = TIM_Status_Success;
            break;
        }

        if ( TIM_Instance->Context->Timestamp.Second < TIM_Timestamp->Second )
        {
            // Not expired
            TIM_Status = TIM_Status_Error;
            break;
        }

        if ( TIM_Instance->Context->Timestamp.Second > TIM_Timestamp->Second )
        {
            // Expired
            TIM_Status = TIM_Status_Success;
            break;
        }

        if ( TIM_Instance->Context->Timestamp.Millisecond < TIM_Timestamp->Millisecond )
        {
            // Not expired
            TIM_Status = TIM_Status_Error;
            break;
        }

        if ( TIM_Instance->Context->Timestamp.Millisecond > TIM_Timestamp->Millisecond )
        {
            // Expired
            TIM_Status = TIM_Status_Success;
            break;
        }

        if ( TIM_Instance->Context->Timestamp.Microsecond < TIM_Timestamp->Microsecond )
        {
            // Not expired
            TIM_Status = TIM_Status_Error;
            break;
        }

        if ( TIM_Instance->Context->Timestamp.Microsecond > TIM_Timestamp->Microsecond )
        {
            // Expired
            TIM_Status = TIM_Status_Success;
            break;
        }

        // Timestamps are equal
        // Consider Expired
        TIM_Status = TIM_Status_Success;
    }
    while ( 0 );
    return TIM_Status;
}

// #############################################################################
// #### Public Variable(s) #####################################################
// #############################################################################

// #############################################################################
// #### File Guard #############################################################
// #############################################################################

#endif /* TIM_WINDOWS */

// #############################################################################
// #### END OF FILE ############################################################
// #############################################################################
