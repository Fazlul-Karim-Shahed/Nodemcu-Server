
const express = require('express')
const { default: axios } = require('axios')
const app = express()

// Middlewares
app.use(express.json())

app.post('/', (req, res) => {

    // console.log(req.body)
    axios.put('https://reserveticket-2b51b-default-rtdb.firebaseio.com/Test/-Nr1kJYXDR5pXpkdc3Gg.json', req.body, {
        headers: {
            'Content-Type': 'application/json'
        }
    }).then(data => {
        res.status(200).send("Data updated")
    })

})
app.get('/', (req, res) => {
    console.log("This is get")
    res.send('Hi Shahed, Welcome to NodeJS')
})


const port = 4000
app.listen(port, () => {
    console.log("Server is running on port " + port);
})