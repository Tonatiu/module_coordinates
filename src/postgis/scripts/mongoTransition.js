/**
 * Module Dependencies
 * */
var mongodb = require('mongodb');
var pg = require('pg');


/**
 * PostgreSQL Config
 * */
var PG_HOST = "127.0.0.1";
var PG_PORT = 5432;
var PG_DATABASE = "municipios";
var PG_USER = "postgres";
var PG_PASSWORD = "root";
var PG_CONNECTION_STRING = "postgres://" + PG_USER + ":" + PG_PASSWORD + "@" + PG_HOST + "/" + PG_DATABASE;


/**
 * MongoDB Config
 * */
var MONGO_HOST = "107.170.232.222";
var MONGO_PORT = 27017;
var MONGO_DB = "susi_db";
var MONGO_COLLECTION = "escenas";


var mongo_insert = function(data, callback){
    var server = new mongodb.Server(MONGO_HOST, MONGO_PORT);
    var db = new mongodb.Db(MONGO_DB, server);
    
    db.open(function (err, client) {
        if(err){
            callback(err, null);
        }
        
        client.collection(MONGO_COLLECTION).insert(data, {}, function(err, records){
            db.close();
            callback(err, records);
        }); 
    });
};

// start
var client = new pg.Client(PG_CONNECTION_STRING);
client.connect(function(err) {
    if(err) {
        console.log('could not connect to postgis', err);
        return -1;
    }
    
    var query = "DELETE FROM transition RETURNING data, ST_AsGeoJSON(the_geom) as the_geom";
    
    client.query(query, function(err, result) {
        client.end();
        
        if(err) {
            console.error('error running the query', err);
            return -1;
        }
        
        var data = [];
        for(var i = 0; i < result.rows.length; i++){
            var geojson = result.rows[i].data;
            geojson.the_geom = JSON.parse(result.rows[i].the_geom);
            
            //epoch time
            var dateString = geojson.scene_date_temp + "T" + geojson.scene_time;
            geojson.scene_date = new Date(dateString).getTime();
            
            delete geojson.scene_date_temp;
            delete geojson.scene_time;
            
            data.push(geojson);
        }
        
        mongo_insert(data, function(err, result){
            if(err) {
                console.error('error inserting the data', err);
                return -1;
            }
            
            console.log(result);
            return 0;
        });
    });
});

