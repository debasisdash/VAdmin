
/**
 * Module dependencies.
 */

var express = require('express')
  , routes = require('./routes')
  , user = require('./routes/user')
  , http = require('http')
  , path = require('path')
  , sql = require('./routes/sql')
  , mysql = require('./routes/mysql')
  , home = require('./routes/index');

var app = express();

// all environments
app.set('port', process.env.PORT || 3000);
app.set('views', __dirname + '/views');
app.set('view engine', 'ejs');
app.use(express.favicon());
app.use(express.logger('dev'));
app.use(express.bodyParser());
app.use(express.methodOverride());
app.use(app.router);
app.use(express.static(path.join(__dirname, 'public')));

// development only
if ('development' === app.get('env')) {
  app.use(express.errorHandler());
}

app.get('/', routes.index);
//app.get('/', sql.readAllRows);
app.get('/users', user.list);

//app.get('/dashboard', function(req,res)
//		{
//			res.render('index');
//		});
//

//app.get('/vm', function(req,res)
//		{
//			res.render('vm');
//		});
//
//app.get('/io', function(req,res)
//		{
//			res.render('io');
//		});
//
//app.get('/memory', function(req,res)
//		{
//			res.render('memory');
//		});
//
//app.get('/charts', function(req,res)
//		{
//			res.render('chart');
//		});
//
//
app.get('/charts', function(req,res)
		{
			res.render('chart');
		});

//app.get('/io',sql.io);

//app.get('/', routes.index);
//app.get('/', sql.readAllRows);
//app.get('/users', user.list);
app.get('/dashboard',routes.index);
app.get('/memory',routes.memory);
app.get('/vm',routes.vm);
app.get('/io',routes.io);
app.get('/login',routes.login);
app.post('/login',routes.login);


http.createServer(app).listen(app.get('port'), function(){
  console.log('Express server listening on port ' + app.get('port'));
});
