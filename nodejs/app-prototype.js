var SerialPort = require("serialport").SerialPort
var serialPort = new SerialPort("/dev/tty.usbmodem411", {
	baudrate: 38400
});

var mongodb = require("mongodb"),
    mongoserver = new mongodb.Server('localhost', mongodb.Connection.DEFAULT_PORT, true),
    db_connector = new mongodb.Db('DevThis', mongoserver, 5);

serialPort.on("open", function () {
	console.log('open');

	var buff = "";
	db_connector.open(function(err, db) {

		serialPort.on('data', function(data) {
			buff += data;

			if(String(data).indexOf('}') > -1){
				
				var collection = db.collection('RoadData');
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

});