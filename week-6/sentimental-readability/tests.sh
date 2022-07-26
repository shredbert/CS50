#!/usr/bin/env bash

# echo "***Grade 3***"
# ./readability.py << EOF
# Congratulations! Today is your day. You're off to Great Places! You're off and away!
# EOF

# echo "***Before Grade 1***"
# ./readability.py << EOF
# One fish. Two fish. Red fish. Blue fish.
# EOF

TEXT="Would you like them here or there? I would not like them here or there. I would not like them anywhere."

echo
echo "***Should print:***"
echo

echo "Text: $TEXT"
echo "Grade 2"
echo "Letters: 80"
echo "Words: 21"
echo "Sentences: 3"
echo "Avg letters / 100 words: 444.44444444444446"
echo "Avg sentences / 100 words: 16.666666666666664"

echo
echo "***Does print:***"
echo

./readability.py << EOF
Would you like them here or there? I would not like them here or there. I would not like them anywhere.
EOF

