/**
 * New node file
 */
"use strict";

var sqlite3 = require('sqlite3').verbose();
var db;

function fetchData(callback, Query) {

	//console.log("\nSQL Query::" + sqlQuery);

	var connection = getConnection();

	connection.query(Query, function(err, rows, fields) {
		if (err) {
			console.log("ERROR: " + err.message);
		} else { // return err or result
			callback(err, rows);
		}
	});
	console.log("\nConnection closed..");
	connection.end();
}


function createDb(req,res) {
    console.log("createDb chain");
    db = new sqlite3.Database('chain.sqlite3', readAllRows(req,res));
}


function createTable(req,res) {
    console.log("createTable lorem");
    db.run("CREATE TABLE IF NOT EXISTS lorem (info TEXT)", insertRows(req,res));
}

function insertRows(req,res) {
    console.log("insertRows Ipsum i");
    var stmt = db.prepare("INSERT INTO lorem VALUES (?)");

    for (var i = 0; i < 10; i++) {
        stmt.run("Ipsum " + i);
    }

    stmt.finalize(readAllRows(req,res));
}

function readAllRows(req,res) {
	db = new sqlite3.Database('chain.sqlite3');
    console.log("readAllRows lorem");
    db.all("SELECT rowid AS id, info FROM lorem", function(err, rows) {
    	
        rows.forEach(function (row) {
            console.log(row.id + ": " + row.info);
        });
        res.end(JSON.stringify(rows));
        
        closeDb();
    });
}

function closeDb() {
    console.log("closeDb");
    db.close();
}

function runChainExample(req,res) {
    createDb();
}

//runChainExample();


exports.createDb = createDb;
exports.readAllRows = readAllRows;
exports.fetchData = fetchData;