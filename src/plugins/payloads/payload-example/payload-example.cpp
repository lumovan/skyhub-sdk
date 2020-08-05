/****************************************************************************
**
** Copyright (C) 2020, Smart Projects Holdings Ltd
** Contact: https://industrial.ugcs.com/contact
**
** This file is part of SkyHub SDK.
**
** BSD 3-Clause License Usage
**
** This file may be used under the terms of the BSD 3-Clause License
** as published by the Open Source Initiative and appearing in the file
** LICENSE included in the packaging of this file. Please review the
** following information to ensure the BSD 3-Clause License requirements
** will be met: https://opensource.org/licenses/BSD-3-Clause.
**
****************************************************************************/

#include "payload-example.h"

#include <monitormessage.h>
#include <positionlog.h>
#include <simconnection.h>

/*!
    \class PayloadExample
    \inmodule SkyHub SDK
    \brief PayloadExample class provides base function of the payload plugin.
    PayloadExample class is given as an example for creating your own plugins
    for connecting the custom payloads to the SkyHub.
    Any payload plugin should be inherited from the IPayloadPlugin parent class.
*/

/*
    namespace C
    This namespace is used to provide meaningful names instead of numerical
    literals ("magic numbers") for special values.

    PeriodUs - period of call of calcRange() function and updating of data
    for logging in position log, us.
    MinRange, MaxRange - minimum/maximum simulation data.
    Delta -  simulation data increment/dicrement value.

    MinValue, MaxValue - minimum/maximum allowed value for data received from
    the simulator. These constants are used in the ScalarSensorData::checkStatus method.

    PayloadId is a unique number that identify the payload type. Only one plugin
    for each Id type can work at the same time. Numbers from 0xC0 to 0xDF are
    reserved for custom payloads. To get data from the custom plugin you need to set the
    same Id in the settings of the custom payload widget in UgCS-CPM.
*/
namespace C {

const int PeriodUs = 100;
const float MinRange = 1;
const float MaxRange = 7;
const float Delta = 0.1f;

const int MinValue = 2;
const int MaxValue = 5;

const int PayloadId = 0xC0;

}

/*!
    \fn PayloadExample::PayloadExample()
    Constructs a PayloadExample and configures the plugin before calling
    the \c start() method.
*/
PayloadExample::PayloadExample()
{
    /*
        The setStartDelay() method is a method of parent class IPayloadPlugin
        provides delay of calling start() method.
    */
    setStartDelay(0);
    m_id = static_cast<PayloadId>(C::PayloadId);
}

/*!
    \fn PayloadExample::~PayloadExample()
    Destructor of PayloadExample. When calling the destructor the plugin stops the
    running timer for which the simulation data were generated.
*/
PayloadExample::~PayloadExample()
{
    if (m_timerId != -1) {
        killTimer(m_timerId);
        m_timerId = -1;
    }
}

/*!
    \fn void PayloadExample::start()
    The startup method should contain all necessary elements to start the plugin
    from its payload:
    \list
        \li payload initialization and configuration
        \li sending the starting sequences
        \li setting the necessary timers, etc.
    \endlist
*/
void PayloadExample::start()
{
    if (m_timerId == -1)
        m_timerId = startTimer(C::PeriodUs);

    /*
        The addParameter() method of the PositionLog class creates the column
        with ID:Parameter name in the position log.
    */
    PositionLog::instance()->addParameter("Value", id());
}

/*!
    \fn void PayloadExample::stop()
    The \c stop() method closes the payload communication and stops the timers
    running in the \c start() method.
*/
void PayloadExample::stop()
{
    if (m_timerId != -1) {
        killTimer(m_timerId);
        m_timerId = -1;
    }
}

/*!
    \fn ConnectionType PayloadExample::connectionType() const
    Return the payload connection type. List of connection types:
    \list
        \li Simulator
        \li Tcp
        \li Uart
        \li Bluetooth
    \endlist
*/
ConnectionType PayloadExample::connectionType() const
{
    return ConnectionType::Simulator;
}

/*!
    \fn PayloadId PayloadExample::payloadId() const
    Return the payload ID number
*/
PayloadId PayloadExample::payloadId() const
{
    return m_id;
}

/*!
    \fn QString PayloadExample::name() const
    Return the payload name
*/
QString PayloadExample::name() const
{
    return "Payload example";
}

/*!
    \fn QString PayloadExample::id() const
    Return the payload text ID
*/
QString PayloadExample::id() const
{
    return "PEX";
}

/*!
    \fn void PayloadExample::timerEvent(QTimerEvent *event)
    The \c timerEvent() method is an overloaded QObject method and allows you to
    process plugin \a event.
*/
void PayloadExample::timerEvent(QTimerEvent *event)
{

    /*
        On the event from the m_timerId timer, a method is called to update the
        m_sensorData and sets m_sensorData.value value to position log.
    */
    if (event->timerId() == m_timerId) {
        calcRange();
        if (m_sensorData.status != ScalarSensorStatusId::SensorError)
            PositionLog::instance()->setValue("Value", m_sensorData.value, id());
    }

    /*
        The telemetryTimerId() is a function of the IPayloadPlugin parent class.
        This method returns the event id from the telemetry timer. The telemetry timer
        is run in the parent constructor.
        In this event the payload data are prepared and sent to UgCS-CPM.
    */
    if (event->timerId() == telemetryTimerId()) {
        ScalarSensorStatusMessage message(static_cast<MonitorMessageId>(C::PayloadId));//UserPayloadMessageId
        message.payload()->value = m_sensorData.value;
        message.payload()->statusId = static_cast<ScalarSensorStatusId>(m_sensorData.status);
        emit dataReceived(MessageId::ArrayId, payloadId(), toByteArray(message));
    }
}

/*!
    \fn void PayloadExample::calcRange()
    This function is a generator of simulation data for this plugin.
*/
void PayloadExample::calcRange()
{
    static float range = C::MinRange;
    static float delta = C::Delta;

    range += delta;
    if (range + delta > C::MaxRange || range + delta < C::MinRange)
            delta = -delta;

    m_sensorData = ScalarSensorData(range, C::MinValue, C::MaxValue);
}
