const express = require('express')
const mongoose = require('mongoose')
const dotenv = require('dotenv')
const servicesRouter = require('./routers/services')
const bodyParser = require('body-parser')
const app = express()

dotenv.config()

mongoose.connect(process.env.DB_CONNECT, {
    useNewUrlParser: true,
    useUnifiedTopology: true,
    useFindAndModify: false,
    useCreateIndex: true
  }, () => console.log('Veritabanına bağlantı sağlandı.'))


app.use(bodyParser.json())
app.use('/api/services/', servicesRouter)

app.listen(process.env.PORT_NAME,process.env.HOST_NAME, () => console.log(`Server Çalışıyor, http://${process.env.HOST_NAME}:${process.env.PORT_NAME}/api/services/`))