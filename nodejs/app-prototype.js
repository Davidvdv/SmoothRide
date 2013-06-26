var express = require('express');
var fs = require('fs');
var app = express();

var SerialPort = require("serialport").SerialPort
var serialPort = new SerialPort("/dev/tty.usbmodem411", {
	baudrate: 38400
});

var mongodb = require("mongodb"),
    mongoserver = new mongodb.Server('localhost', mongodb.Connection.DEFAULT_PORT, true),
    db_connector = new mongodb.Db('DevThis', mongoserver, 5);

db_connector.open(function(err, db) {

	var collection = db.collection('RoadData');

	serialPort.on("open", function () {
		console.log('open');

		var buff = "";
		serialPort.on('data', function(data) {
			buff += data;

			if(String(data).indexOf('}') > -1){
				
				var verklaring = JSON.parse(buff.toString());
				
				// Add some geo sugar
				verklaring.geolocation = {"lat":51.917368, "lng":4.484805};

				// Sla die ding op G!
				collection.insert(verklaring);

				// BUFFEL. DAAGH.
				buff = "";
			}
		});
	});
	
	app.get('/roaddata.json', function(req, res) {

		collection.find().toArray(function(err, items){
			console.log(find);
			res.json(items);
		});
	});

	app.get('/', function(req, res) {
		res.type('html');
		res.send(fs.readFileSync('index.html'));
	});

	app.listen(3000);
});