const express = require('express')
const Sensor = require('../model/Sensor')
const router = express.Router()

router.get('/',async (req,res)=>{
    try{
        const getall = await Sensor.find()
        res.json(getall)
    }catch (err){
        res.json({message: err})
    }
})
router.post('/',async (req,res)=>{
    const sensor =  Sensor({
        humidity: req.body.humidity,
        temperature: req.body.temperature,
        distance: req.body.distance
    })
    try {
        const savedSensor = await sensor.save()
        res.send(savedSensor)
    } catch (error) {
        res.status(400).send(error)
    }
})

module.exports = router