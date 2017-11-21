#!/bin/bash

STR=$1
diff <(echo $STR | ./ft_ssl base64 ) <(echo $STR | base64 )
