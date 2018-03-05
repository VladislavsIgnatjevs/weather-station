function update() {
    var startPos,
        startLat = 0,
        api_key = '',
        startLon = 0,
        geoSuccess = function(position) {
            startPos = position;
            startLat = startPos.coords.latitude;
            startLon = startPos.coords.longitude;

            console.log('Current Latitude: ' + startLat);
            console.log('Current Longitude: ' + startLon);

            //call api
            $.getJSON("http://api.openweathermap.org/data/2.5/weather?lat=" + startLat +"&lon=" + startLon + '&appid=' + api_key + '&units=metric' ,function(result){


                $('#city').html(result.name);

                $('#humidity').html(result.main.humidity + '%');
                $('#pressure').html(result.main.pressure + ' hPa');
                $('#clouds').html(result.clouds.all + '%');
                $('#temp').html(result.main.temp + ' C');
                $('#forecast').html(result.weather[0].main + ' (' + result.weather[0].description + ')');

                var wID = result.weather[0].id;

                        if ( wID < 300) {
                            $('#current_weather').val("thunder");
                        } else if (wID > 300 && wID < 600) {
                            $('#current_weather').val("rain");
                        } else if (wID > 600 && wID < 700) {
                            $('#current_weather').val("snow");
                        } else if (wID > 700 && wID < 800) {
                            $('#current_weather').val("mist");
                        } else if (wID == 800) {
                            $('#current_weather').val("clear");
                        } else if (wID > 800 && wID < 900) {
                            $('#current_weather').val("cloud");
                        } else if (wID > 900 && wID < 910) {
                            $('#current_weather').val("extreme");
                        } else if(wID > 950 && wID < 955) {
                            $('#current_weather').val("breeze");
                        } else if (wID > 955 && wID < 960) {
                            $('#current_weather').val("gale");
                        } else if (wID > 960) {
                            $('#current_weather').val("storm");
                        } else {
                            $('#current_weather').val("");
                        }


            })
                .done(function () {
                    console.log("Successful call to weather API");
                    console.log('Updated at ' + $.format.date(new Date() , 'dd/MM/yyyy HH:mm:ss'));
                })
                .fail(function (response) {
                    console.log(response.responseJSON.message);
                })
            ;


            $('#startLat').html(startPos.coords.latitude);
            $('#startLon').html(startPos.coords.longitude);

        };
    //set geo location
    navigator.geolocation.getCurrentPosition(geoSuccess);
}