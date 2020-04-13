#!/bin/bash

function demo_classic_api {
  ./classic-api/run.sh
}

function demo_rm_manager {
  echo "Not yet implemented"
}

function demo_cbs {
  echo "Not yet implemented"
}

function help {
  echo
  echo "--> Please pick one of the available demos:"
  echo "1. Periodic tasks using Classic API"
  echo "2. Periodic tasks using Rate Monotonic Manager"
  echo "3. CBS-scheduled periodic tasks"
  echo "4. Exit"
  echo -n "--> "
}

echo "#------------------------------------------------#"
echo "#   Welcome to this interactive demo of RTEMS!   #"
echo "#------------------------------------------------#"
echo "# Created by Bart van Oort and Jasper van Esveld #"
echo "# for the RTOS Survey of Real-Time Systems 2020  #"
echo "# as taught by Mitra Nasri at the TU Delft       #"
echo "#------------------------------------------------#"
echo "# For the source code of this demo, see the      #"
echo "# folders around this script, or check our Git   #"
echo "# repository: TODO ADD LINK                      #"

while :
do
  help
  read demo
  case $demo in
	1)
		echo
    echo "-> Running Classic API demo"
    echo
    demo_classic_api
		;;
	2)
    echo
    echo "-> Running Rate Monotonic Manager demo"
    echo
		demo_rm_manager
		;;
  3)
    echo
    echo "-> Running CBS scheduler demo"
    echo
    demo_cbs
    ;;
  4)
    break
    ;;
  help)
    ;;
	exit)
		break
		;;
  easter)
    echo "-> Ha, you've found the easter egg!"
    echo "-> Have a cookie ;)"
    ;;
  *)
    echo
    echo "-> Invalid input: $demo"
    ;;
  esac
done
echo 
echo "Bye!"
