const mongoose = require('mongoose')
const SensorSchema = new mongoose.Schema({
    humidity: {type: Number, required: true},
    temperature: {type: Number, required: true},
    distance: {type: Number, required: true},
    date: {type: Date, default:Date.now}
},{collection: 'sensors'})
module.exports = mongoose.model('Sensor',SensorSchema)