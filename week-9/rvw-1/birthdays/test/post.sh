#!/usr/bin/env bash
curl -X POST -F birth_name="Farts McGee" -F birth_month=12 -F birth_day=31 -L http://127.0.0.1:5000 -i
