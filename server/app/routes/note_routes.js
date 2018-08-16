// note_routes.js
var ObjectID = require('mongodb').ObjectID;
module.exports = function (app, db) {

    app.get('/', (req, res) => {
        res.send("Welcome to the homepage???");
    });


    app.get('/notes/:id', (req, res) => {
        const id = req.params.id;
        const details = { '_id': new ObjectID(id) };
        db.collection('notes').findOne(details, (err, item) => {
            if (err) {
                res.send({ 'error': 'An error has occurred' });
            } else {
                res.send(item);
            }
        });
    });
    

    app.get('/gyro', (req, res) => {
        
        var mysort = {'time': -1 };
        db.collection("gyro").find().sort(mysort).toArray(function (err, result) {
            if (err) {
                res.send({ 'error': 'An error has occurred' });
            } else {
                res.send(result[0]);
            }
        });
        
    });

    app.get('/mag', (req, res) => {

        var mysort = { 'time': -1 };
        db.collection("mag").find().sort(mysort).toArray(function (err, result) {
            if (err) {
                res.send({ 'error': 'An error has occurred' });
            } else {
                res.send(result[0]);
            }
        });

    });

    app.get('/xcel', (req, res) => {

        var mysort = { 'time': -1 };
        db.collection("xcel").find().sort(mysort).toArray(function (err, result) {
            if (err) {
                res.send({ 'error': 'An error has occurred' });
            } else {
                res.send(result[0]);
            }
        });

    });



    app.put('/notes/:id', (req, res) => {
        const id = req.params.id;
        const details = { '_id': new ObjectID(id) };
        const note = { title: req.body.title, gyrox: req.body.gyrox, gyroy: req.body.gyroy, gyroz: req.body.gyroz};
        db.collection('notes').update(details, note, (err, result) => {
            if (err) {
                res.send({ 'error': 'An error has occurred' });
            } else {
                res.send(note);
            }
        });
    });

    app.post('/gyro', (req, res) => {
        const note = { time: (new Date).getTime(), gyrox: req.body.gyrox, gyroy: req.body.gyroy, gyroz: req.body.gyroz };
        db.collection('gyro').insert(note, (err, result) => {
            if (err) {
                res.send({ 'error': 'An error has occurred' });
            } else {
                res.send(result.ops[0]);
            }
        });
    });
    app.post('/mag', (req, res) => {
        const note = { time: (new Date).getTime(), magx: req.body.magx, magy: req.body.magy, magz: req.body.magz };
        db.collection('mag').insert(note, (err, result) => {
            if (err) {
                res.send({ 'error': 'An error has occurred' });
            } else {
                res.send(result.ops[0]);
            }
        });
    });
    app.post('/xcel', (req, res) => {
        const note = { time: (new Date).getTime(), xcelx: req.body.xcelx, xcely: req.body.xcely, xcelz: req.body.xcelz };
        db.collection('xcel').insert(note, (err, result) => {
            if (err) {
                res.send({ 'error': 'An error has occurred' });
            } else {
                res.send(result.ops[0]);
            }
        });
    });

    app.post('/notes', (req, res) => {
        const note = { time: (new Date).getTime(), title: req.body.title, gyrox: req.body.gyrox, gyroy: req.body.gyroy, gyroz: req.body.gyroz };
        db.collection('notes').insert(note, (err, result) => {
            if (err) {
                res.send({ 'error': 'An error has occurred' });
            } else {
                res.send(result.ops[0]);
            }
        });
    });
};