#!/usr/bin/env bash
# Won't work -- changed to POST request @ /delete
curl -X DELETE -F id=3 http://127.0.0.1:5000/modify
