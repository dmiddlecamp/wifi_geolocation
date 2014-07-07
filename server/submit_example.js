/**
 * Created by middleca on 4/4/14.
 */


var request = require('request');
var moment = require('moment');

var submitData = {
    "wifi": [
        { "key": "AA:BB:CC:DD:EE:FF", "signal": -10 }
    ]
};

var submit = function () {
    console.log("Testing submit endpoint");

    var request_url = "https://location.services.mozilla.com/v1/search?key=nightly";


    request({
        uri: request_url,
        method: "POST",
        body: JSON.stringify(submitData),
        'content-type': 'application/json',
        json: true
    }, function (error, response, body) {

        if (error) {
            console.log("Error! ", error);
        }

        console.log("got back ", body);
    });

};

submit();
