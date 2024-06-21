#!/bin/bash

echo "run server"
./build/src/splan-server&

echo "wait for server"
sleep 2

pid=$(pidof splan-server)
echo "server pid: ${pid}"


echo "test health endpoint"
health=$(curl "http://localhost:8080/health")
expected_healt="{\"message\": \"Not implemented yet\"}"
if [[ $health != $expected_healt ]]; then
    kill $pid
    exit -1
fi


echo "test faculties endpoint"
faculties=$(curl "http://127.0.0.1:8080/faculties")
expected_faculties='[[{"id":3,"shortname":"*RO","name":"Rosenheim (Hochschule)"},{"id":6,"shortname":"AÖ","name":"Altötting (Berufliche Oberschule Inn-Salzach)"},{"id":8,"shortname":"BGL","name":"Ainring (Akademie Berchtesgadener Land)"},{"id":7,"shortname":"Bgh","name":"cb - Hochschulinstitut Burghausen"},{"id":9,"shortname":"CC","name":"Campus Chiemgau Traunstein"},{"id":4,"shortname":"MÜ","name":"Mühldorf (Haus der Wirtschaft)"},{"id":5,"shortname":"WS","name":"Wasserburg (RoMed Klinik)"}]]â'

if [[ "$faculties" != "$expected_faculties" ]]; then
    echo "faculties endpoint test failed"
    kill $pid
    exit -1
fi

echo "test timetable endpoint"
timetable=$(curl "http://127.0.0.1:8080/timetable")
expected_timetable="{\"message\": \"Not implemented yet\"}"

if [[ $timetable != $expected_timetable ]]; then
    echo "timetable endpoint test failed"
    kill $pid
    exit -1
fi

echo "test semesters endpoint"
semesters=$(curl "http://127.0.0.1:8080/semesters")
expected_semesters='[[{"id":3,"shortname":"*RO","name":"Rosenheim (Hochschule)"},{"id":6,"shortname":"AÖ","name":"Altötting (Berufliche Oberschule Inn-Salzach)"},{"id":8,"shortname":"BGL","name":"Ainring (Akademie Berchtesgadener Land)"},{"id":7,"shortname":"Bgh","name":"cb - Hochschulinstitut Burghausen"},{"id":9,"shortname":"CC","name":"Campus Chiemgau Traunstein"},{"id":4,"shortname":"MÜ","name":"Mühldorf (Haus der Wirtschaft)"},{"id":5,"shortname":"WS","name":"Wasserburg (RoMed Klinik)"}]]R'

if [[ "$semesters" != "$expected_semesters" ]]; then
    echo "semesters endpoint test failed"
    kill $pid
    exit -1
fi

echo "test non existing endpoint"
not_found=$(curl "http://127.0.0.1:8080/not_found")
expected_not_found="{\"message\": \"404 Not found\"}"

if [[ $not_found != $expected_not_found ]]; then
    echo "non existing endpoint test failed"
    kill $pid
    exit -1
fi

echo "kill ${pid}"
kill ${pid}
