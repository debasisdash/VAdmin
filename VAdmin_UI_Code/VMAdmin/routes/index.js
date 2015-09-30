
/*
 * GET home page.
 */
var inspect = require('util').inspect;
var sqlite3 = require('sqlite3').verbose();



exports.index = function(req, res){
	var memory =null;
	var ioreport = null;
	var process= null;
	var cpu=null;
	var paging=null;
	var disk = null;
    var db = new sqlite3.Database('/Users/Neeraj/VAdminDB');
console.log("readAllRows lorem");
//db.all("SELECT rowid AS id, info FROM lorem", function(err, rows) {
	db.all("SELECT * from CPUStats", function(err, rows)
			{
			cpu=rows;
			rows.forEach(function (cpu) {
			console.log("CPU = " + cpu.nice + ": ");
			
			});
			db.all("SELECT * from Memory", function(err, rows)
					{
						memory = rows;
						rows.forEach(function (memory) {
					    console.log("Memroy = " + memory.nodeAdr + ": " + memory.Memused);
						
						});
						db.all("SELECT * from IOReport", function(err, rows)
								{
									ioreport = rows;
									rows.forEach(function (ioreport) {
								    console.log("IO report = " + ioreport.tps + ": ");
									
									});
									db.all("SELECT * from Process", function(err, rows)
											{
												process = rows;
												rows.forEach(function (process) {
											    console.log("Process = " +  process.plist_sz + ": ");
												
												});	
												db.all("SELECT * from Paging", function(err, rows)
														{
														paging = rows;
															rows.forEach(function (paging) {
														    console.log("Paging = " + paging.pgpgin + ": ");
															
															});
															db.all("SELECT * from Disk", function(err, rows)
																	{
																	disk = rows;
																		rows.forEach(function (disk) {
																	    console.log("Disk = " + disk.avail + ": ");
																		
																		});																		
																		res.render('index', { title: 'Express',memory:memory, cpu:cpu, ioreport:ioreport, process:process, paging:paging });        
																	});
															
														//	res.render('index', { title: 'Express',memory:memory, cpu:cpu, ioreport:ioreport, process:process, paging:paging });        
														});
												
												//res.render('index', { title: 'Express',memory:memory, cpu:cpu, ioreport:ioreport, process:process });        
											});
									
									//res.render('index', { title: 'Express',memory:memory, cpu:cpu, ioreport:ioreport});        
								});
						
						
						//res.render('index', { title: 'Express',memory:memory, cpu:cpu});        
					});
			//cpu=rows;
    
});

};


//	var db = new sqlite3.Database('VAdminDB');
//    //console.log("readAllRows lorem");
//    db.all("SELECT * FROM Memory", function(err, rows) {  
//        if(err){
//            console.log("error in CPUStats connect");
//        }
//        else{
//    	 //console.log(inspect(rows));
//    	res.render('index', { title: 'Express',rows:rows});
//        }
//    });
//};


exports.dashboard = function(req,res){
			res.render('index');
};


exports.vm = function(req, res){
	var memory =null;
	var ioreport = null;
	var process= null;
	var cpu=null;
	var paging=null;
	var disk = null;
    var db = new sqlite3.Database('/Users/Neeraj/VAdminDB');
console.log("readAllRows lorem");
//db.all("SELECT rowid AS id, info FROM lorem", function(err, rows) {
	db.all("SELECT * from CPUStats", function(err, rows)
			{
			cpu=rows;
			rows.forEach(function (cpu) {
			console.log("CPU = " + cpu.nice + ": ");
			
			});
			db.all("SELECT * from Memory", function(err, rows)
					{
						memory = rows;
						rows.forEach(function (memory) {
					    console.log("Memroy = " + memory.nodeAdr + ": " + memory.Memused);
						
						});
						db.all("SELECT * from IOReport", function(err, rows)
								{
									ioreport = rows;
									rows.forEach(function (ioreport) {
								    console.log("IO report = " + ioreport.tps + ": ");
									
									});
									db.all("SELECT * from Process", function(err, rows)
											{
												process = rows;
												rows.forEach(function (process) {
											    console.log("Process = " +  process.plist_sz + ": ");
												
												});	
												db.all("SELECT * from Paging", function(err, rows)
														{
														paging = rows;
															rows.forEach(function (paging) {
														    console.log("Paging = " + paging.pgpgin + ": ");
															
															});
															db.all("SELECT * from Disk", function(err, rows)
																	{
																	disk = rows;
																		rows.forEach(function (disk) {
																	    console.log("Disk = " + disk.avail + ": ");
																		
																		});																		
																		res.render('vm', { title: 'Express',memory:memory, cpu:cpu, ioreport:ioreport, process:process, paging:paging });        
																	});
															
														//	res.render('index', { title: 'Express',memory:memory, cpu:cpu, ioreport:ioreport, process:process, paging:paging });        
														});
												
												//res.render('index', { title: 'Express',memory:memory, cpu:cpu, ioreport:ioreport, process:process });        
											});
									
									//res.render('index', { title: 'Express',memory:memory, cpu:cpu, ioreport:ioreport});        
								});
						
						
						//res.render('index', { title: 'Express',memory:memory, cpu:cpu});        
					});
			//cpu=rows;
    
});

};


exports.memory = function(req, res){
	var memory =null;
	var ioreport = null;
	var process= null;
	var cpu=null;
	var paging=null;
	var disk = null;
    var db = new sqlite3.Database('/Users/Neeraj/VAdminDB');
console.log("readAllRows lorem");
//db.all("SELECT rowid AS id, info FROM lorem", function(err, rows) {
	db.all("SELECT * from CPUStats", function(err, rows)
			{
			cpu=rows;
			rows.forEach(function (cpu) {
			console.log("CPU = " + cpu.nice + ": ");
			
			});
			db.all("SELECT * from Memory", function(err, rows)
					{
						memory = rows;
						rows.forEach(function (memory) {
					    console.log("Memroy = " + memory.nodeAdr + ": " + memory.Memused);
						
						});
						db.all("SELECT * from IOReport", function(err, rows)
								{
									ioreport = rows;
									rows.forEach(function (ioreport) {
								    console.log("IO report = " + ioreport.tps + ": ");
									
									});
									db.all("SELECT * from Process", function(err, rows)
											{
												process = rows;
												rows.forEach(function (process) {
											    console.log("Process = " +  process.plist_sz + ": ");
												
												});	
												db.all("SELECT * from Paging", function(err, rows)
														{
														paging = rows;
															rows.forEach(function (paging) {
														    console.log("Paging = " + paging.pgpgin + ": ");
															
															});
															db.all("SELECT * from Disk", function(err, rows)
																	{
																	disk = rows;
																		rows.forEach(function (disk) {
																	    console.log("Disk = " + disk.avail + ": ");
																		
																		});																		
																		res.render('memory', { title: 'Express',memory:memory, cpu:cpu, ioreport:ioreport, process:process, paging:paging });        
																	});
															
														//	res.render('index', { title: 'Express',memory:memory, cpu:cpu, ioreport:ioreport, process:process, paging:paging });        
														});
												
												//res.render('index', { title: 'Express',memory:memory, cpu:cpu, ioreport:ioreport, process:process });        
											});
									
									//res.render('index', { title: 'Express',memory:memory, cpu:cpu, ioreport:ioreport});        
								});
						
						
						//res.render('index', { title: 'Express',memory:memory, cpu:cpu});        
					});
			//cpu=rows;
    
});

};




exports.charts = function(req,res){
			res.render('chart');
};


exports.login = function(req,res){
	res.render('login');
};



exports.io = function(req,res){
			res.render('io');
};
