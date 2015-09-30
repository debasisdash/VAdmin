/**
 * New node file
 */

var sqlite3 = require('sqlite3').verbose();
var db = new sqlite3.Database('mydb.db');
var check;

var ejs = require("ejs");

var mysql = require('./mysql.js');



/*
function readAllRows(req,res) {
	var db = new sqlite3.Database('mydb.db');
    console.log("readAllRows lorem");
    db.all("SELECT rowid AS id, name FROM COMPANY", function(err, rows) {
        rows.forEach(function (row) {
            console.log(row.id + ": " + row.name);
        });
      //  closeDb();
    });
}
*/

function readAllRows(req,res) {
	db = new sqlite3.Database('chain.sqlite3');
    console.log("readAllRows lorem");
    db.all("SELECT rowid AS id, info FROM lorem", function(err, rows) {
    	
        rows.forEach(function (row) {
            console.log(row.id + ": " + row.info);
        });
        res.end(JSON.stringify(rows));
        
        //closeDb();
    });
}

function myfunc(req, res) {
db.serialize(function() {

//  db.run("ATTACH DATABASE 'mydb.db' as 'TEST'");
  db.all("SELECT ID FROM COMPANY", function(err, rows) {
      rows.forEach(function (row) {
          console.log(row.id + ": " + row.name);
      });

//  db.each("select ID from COMPANY", function(err, row) {
//    //  console.log(row.id + ": " + row.info);
//	  console.log(row.name + " " +  row.age + " " +  row.address + " " +  row.salary);
  });
});

db.close();

}



function io(req,res) {
	var service_data=null;
	var cityName=null;
	var CPUStats = null;
	var ioWait=null;
	ioWait = req.param("ioWait");
//	var serviceId=req.param("serviceId");
//	console.log("City:-"+cityName);
	//var query = "select  s.*,c.*,m.* from serviceinfo s,city c,service m where s.cityid_si=c.city_id and s.serviceid_si=m.serviceid and cityid_si=(select city_id from city where cityname='"+cityName+"') and serviceid_si='" + serviceId +"';" ;
	var query = "select i.* from CPUStats";
   
	console.log("Query is:" + query);
	
	mysql.fetchData(function(err, results) {
		if (err) {
			throw err;
		} else {
			if (results.length > 0) {
				for ( var i = 0; i < results.length; i++) {
					console.log(results[i].count);
				} 
				
				
				//service_data = results;
				CPUStats = results;
				
				//console.log(state);
				res.render('io', {
					CPUStats : CPUStats,				
				});	
			}
		}
	}, query);	
}



exports.myfunc = myfunc;
exports.io=io;
//exports.readAllRows = readAllRows;
