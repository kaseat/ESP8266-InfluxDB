// Copyright 2018 Oleg Petrochenko
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//   http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#pragma once
#include "InfluxMeasurement.h"

	/**
	* \brief Represents possible InfluxDB operation statuses.
	*/
	typedef enum
	{
		InfluxOk = 0x30,
		InfluxNoResponse = 0x31,
		InfluxNoSuchDb = 0x32,
		InfluxDefaultHostNotSet = 0x33,
		InfluxDefaultDbNotSet = 0x34,
		InfluxNothingToSend = 0x35
	} InfluxStatus;

	/**
	* \brief InfluxDB communication class.
	*/
	class InfluxDB
	{
	public:
		/**
		* \brief Default ctor.
		*/
		InfluxDB() {};
		/**
		* \brief Set default host name.
		*/
		void setDefaultHost(String hostName);
		/**
		* \brief Set default database name.
		*/
		void setDefaultDb(String dbName);
		/**
		* \brief Try to connect to a database.
		* \param hostName InfluxDB host name.
		* \param dbName Database name.
		* \return Returns operation status.
		*/
		InfluxStatus testConnection(String hostName, String dbName);
		/**
		* \brief Try to connect to a database to a default host.
		* \param dbName Database name.
		* \return Returns operation status.
		*/
		InfluxStatus testConnection(String dbName);
		/**
		* \brief Try to connect to a default host and a default database.
		* \return Returns operation status.
		*/
		InfluxStatus testConnection();
		/**
		* \brief Append measurement into the database (will store measurement data locally,
		* to send mmultiple measurements stored locally in one request use 'writeMultiplePoints' method).
		* \param dbName Database name.
		*/
		void appendMeasurement(InfluxMeasurement measurement);
		/**
		* \brief Try to send measurement to a database.
		* \param hostName InfluxDB host name.
		* \param dbName Database name.
		* \param measurement Measurement to be sent.
		* \return Returns operation status.
		*/
		InfluxStatus writePoint(String hostName, String dbName, InfluxMeasurement measurement);
		/**
		* \brief Try to send measurement to a database to a default host.
		* \param dbName Database name.
		* \param measurement Measurement to be sent.
		* \return Returns operation status.
		*/
		InfluxStatus writePoint(String dbName, InfluxMeasurement measurement);
		/**
		* \brief Try to send measurement to a default host and to a default database.
		* \param measurement Measurement to be sent.
		* \return Returns operation status.
		*/
		InfluxStatus writePoint(InfluxMeasurement measurement);
		/**
		* \brief Try to send locally added measurements to the specified host and specified database.
		* \param hostName InfluxDB host name.
		* \param dbName Database name.
		* \return Returns operation status.
		*/
		InfluxStatus writeMultiplePoints(String hostName, String dbName);
		/**
		* \brief Try to send locally added measurements to a default host and to the specified database.
		* \param dbName Database name.
		* \return Returns operation status.
		*/
		InfluxStatus writeMultiplePoints(String dbName);
		/**
		* \brief Try to send locally added measurements to a default host and to a default database.
		* \return Returns operation status.
		*/
		InfluxStatus writeMultiplePoints();

	private:
		InfluxStatus write(String hostName, String dbName, String data);
		String dataToSend;
		String defaultHostName;
		String defaultDbName;
	};

#if !defined(NO_GLOBAL_INSTANCES) && !defined(NO_GLOBAL_INFLUX_DB)
	extern InfluxDB Influx;
#endif
