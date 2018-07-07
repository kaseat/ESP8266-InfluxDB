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
#include <Arduino.h>

/**
* \brief Represents InfluxDB measurement data.
*/
class InfluxMeasurement
{
public:
	/**
	* \brief Create measurement instance.
	* \param name Measurement name.
	*/
	InfluxMeasurement(String name);
	/**
	* \brief Add field to a measurement.
	* \param key Fiend key.
	* \param value Field value (float).
	*/
	void addField(String key, float value);
	/**
	* \brief Add field to a measurement.
	* \param key Fiend key.
	* \param value Field value (integer).
	*/
	void addField(String key, int value);
	/**
	* \brief Add tag to a measurement.
	* \param key Tag key.
	* \param value Tag value (integer).
	*/
	void addTag(String key, String value);
	/**
	* \brief Get string representation of the measurement.
	* \param key Tag key.
	* \param value Tag value (integer).
	* \return Returns string representation of the measurement.
	*/
	String toString();

private:
	String fields;
	String tags;
	String name;
};
