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


#include "InfluxDB.h"
#include <ESP8266HTTPClient.h>

void InfluxDB::setDefaultHost(String hostName)
{
	defaultHostName = hostName;
}

void InfluxDB::setDefaultDb(String dbName)
{
	defaultDbName = dbName;
}

InfluxStatus InfluxDB::createDatabase(String dbName)
{
	return defaultHostName == ""
		? InfluxDefaultHostNotSet
		: createDatabase(defaultHostName, dbName);
}

InfluxStatus InfluxDB::createDatabase(String hostName, String dbName)
{
	return manageDb(hostName, dbName, "create");
}

InfluxStatus InfluxDB::dropDatabase(String dbName)
{
	return defaultHostName == ""
		? InfluxDefaultHostNotSet
		: dropDatabase(defaultHostName, dbName);
}

InfluxStatus InfluxDB::dropDatabase(String hostName, String dbName)
{
	return manageDb(hostName, dbName, "drop");
}

InfluxStatus InfluxDB::testHostConnection()
{
	return defaultHostName == ""
		? InfluxDefaultHostNotSet
		: testHostConnection(defaultHostName);
}

InfluxStatus InfluxDB::testHostConnection(String hostName)
{
	HTTPClient http;
	http.begin("http://" + hostName + "/ping");

	auto result = http.GET() == HTTP_CODE_NO_CONTENT
		? InfluxOk
		: InfluxNoResponse;

	http.end();
	return result;
}

InfluxStatus InfluxDB::testDbConnection()
{
	return defaultDbName == ""
		? InfluxDefaultDbNotSet
		: testDbConnection(defaultDbName);
}

InfluxStatus InfluxDB::testDbConnection(String dbName)
{
	return defaultHostName == ""
		? InfluxDefaultHostNotSet
		: testDbConnection(defaultHostName, dbName);
}

InfluxStatus InfluxDB::testDbConnection(String hostName, String dbName)
{
	HTTPClient http;
	http.begin("http://" + hostName + "/query?q=show%20databases");

	auto result = http.GET() == HTTP_CODE_OK
		? http.getString().indexOf(dbName) > 0
			? InfluxOk
			: InfluxNoSuchDb
		: InfluxNoResponse;

	http.end();
	return result;
}

void InfluxDB::appendMeasurement(InfluxMeasurement measurement)
{
	dataToSend == ""
		? dataToSend = measurement.toString()
		: dataToSend += "\n" + measurement.toString();
}

InfluxStatus InfluxDB::writePoint(InfluxMeasurement measurement)
{
	return defaultDbName == ""
		? InfluxDefaultDbNotSet
		: writePoint(defaultDbName, measurement);
}

InfluxStatus InfluxDB::writePoint(String dbName, InfluxMeasurement measurement)
{
	return defaultHostName == ""
		? InfluxDefaultHostNotSet
		: writePoint(defaultHostName, dbName, measurement);
}

InfluxStatus InfluxDB::writePoint(String hostName, String dbName, InfluxMeasurement measurement)
{
	return write(hostName, dbName, measurement.toString());
}

InfluxStatus InfluxDB::writeMultiplePoints()
{
	return defaultDbName == ""
		? InfluxDefaultDbNotSet
		: writeMultiplePoints(defaultDbName);
}

InfluxStatus InfluxDB::writeMultiplePoints(String dbName)
{
	return defaultHostName == ""
		? InfluxDefaultHostNotSet
		: writeMultiplePoints(defaultHostName, dbName);
}

InfluxStatus InfluxDB::writeMultiplePoints(String hostName, String dbName)
{
	auto response = dataToSend == ""
		? InfluxNothingToSend
		: write(hostName, dbName, dataToSend);

	dataToSend = "";
	return response;
}

InfluxStatus InfluxDB::write(String hostName, String dbName, String data)
{
	HTTPClient http;
	http.begin("http://" + hostName + "/write?db=" + dbName);
	http.addHeader("Content-Type", "text/plain");

	auto result = http.POST(data) == HTTP_CODE_NO_CONTENT
		? InfluxOk
		: InfluxNoResponse;

	http.end();
	return result;
}

InfluxStatus InfluxDB::manageDb(String hostName, String dbName, String action)
{
	HTTPClient http;
	http.begin("http://" + hostName + "/query?q=" + action + "%20database%20\"" + dbName + "\"");

	auto result = http.POST("") == HTTP_CODE_OK
		? InfluxOk
		: InfluxNoResponse;

	http.end();
	return result;
}

#if !defined(NO_GLOBAL_INSTANCES) && !defined(NO_GLOBAL_INFLUX_DB)
InfluxDB Influx;
#endif
