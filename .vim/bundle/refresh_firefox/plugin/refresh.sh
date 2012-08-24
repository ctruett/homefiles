#!/usr/bin/bash
nc -w 1  localhost 4242 <<EOF  > /dev/null
content.location.reload(true)
repl.quit()
EOF
