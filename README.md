# ESP8266 InfluxDB HTTP API client
## Abstract
This library intended to simplify InfluxDB and ESP8266 interaction using Arduino IDE. This library adds global InfluxDB instance called 'Influx' so you can acces 'Influx' from any part of your code. You can disable it by defining NO_GLOBAL_INFLUX_DB. Also this library represents 'measurement' class for easy [InfluxDB points](https://docs.influxdata.com/influxdb/v1.5/concepts/glossary/#point) management.
## Usage
This library implements [measurement](https://docs.influxdata.com/influxdb/v1.5/concepts/glossary/#measurement) data structure. You can add any number of [tags](https://docs.influxdata.com/influxdb/v1.5/concepts/glossary/#tag) and [fields](https://docs.influxdata.com/influxdb/v1.5/concepts/glossary/#field) to your measurement:
```C++
auto m = InfluxMeasurement("temperature");
m.addField("value", 19.3);
m.addTag("greenhouse", "tomatoes");
m.addTag("sensor type", "air");
```
After you create and fill measurement you can send it to remote database immediately:
```C++
Influx.writePoint("hostName", "dbName", m);
```
Or you can store it locally for further sending with other measurements (batching measurements results in much higher performance):
```C++
Influx.appendMeasurement(m);
```
After you retrieve desired measurements and store them by using 'Influx.appendMeasurement' you can send them all together in a single request to the database using 'Influx.writeMultiplePoints' method:
```C++
Influx.writeMultiplePoints("hostName", "dbName", m);
```
## Other features
You can set default host name:
```C++
Influx.setDefaultHost("hostName");
```
So you won't need to specify it each time you send points:
```C++
Influx.writePoint("dbName", m);
```
You can also set default database name:
```C++
Influx.setDefaultDb("dbName");
```
And send points this way:
```C++
Influx.writePoint(m);
```