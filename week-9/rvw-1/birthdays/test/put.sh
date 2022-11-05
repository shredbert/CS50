#!/usr/bin/env bash
# Won't work -- changed to POST request @ /update
curl -X PUT -F id=3 -F birth_name="Lady FartBrains" -F birth_month=6 -F birth_day=9 http://127.0.0.1:5000/modify
