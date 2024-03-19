#!/bin/bash

GREEN='\033[0;32m'
BLUE='\033[0;36m'
PURPLE='\033[1;35m'
YELLOW='\033[0;33m'
NORMAL='\033[0m'  # Define NORMAL as reset (in ASNI)

clear

# Print a message to the user
echo -e "${BLUE}Welcome to the Nonogram solver from Vasileios Filippos Skarleas and Yanis Sadoun. Once you are ready to start exploring the capabilities of the software simply press ENTER"
echo -e "${GREEN}Bienvenue dans le Pickross solver de Vasileios Filippos Skarleas et Yanis Sadoun. Une fois que vous êtes prêt à commencer de decouvrir le logiciel, appuyez simplement sur ENTER"

# Read a line of input from the user
read input

# If the user presses Enter, run the specified commands
if [[ -n "$input" ]]; then
  echo -e "${PURPLE}You did not press ENTER and the program will terminate"
else
  # Run the initial commands
  clear
  echo -e "${PURPLE}Running commands..."
  make clean
  make
  clear
  echo -e "${NORMAL}This software allows you to visualise the function's T responses in several tests according to project's needs, as well as solve nonogram puzzles (one or more tests on the same time)\n"
  echo -e "${BLUE}NOTE:${NORMAL} In order to implement tests, manually or automaticly then follow the instructions mentioned at https://github.com/vskarleas/ROB3-S6-Nonogram before choosing a command from below"
  echo -e "++++++++++++++++++++++++++++++++++++++++++++++++++++++++"

  # Infinite loop with user options
  while true; do
    echo -e "\n==========================================================\nEnter a command (auto, complet, partial, t_tests, stop):"
    read command

    case "$command" in
      auto)
        ./automatic
        sleep 5
        ;;
      t_tests)
        ./t_tests
        sleep 5
        ;;
      complet)
        ./complet
        sleep 5
        ;;
      partial)
        ./partial
        sleep 5
        ;;
      stop)
        break  # Exit the loop
        ;;
      *)
        echo -e "${YELLOW}\nInvalid command. Please try again!${NORMAL}"
        ;;
    esac
  done

  # Commands to execute after exiting the loop
  make clean
  clear
  echo -e "${GREEN}Programs has been successfully terminated"
  echo -e "${NORMAL}Thank you! | ${BLUE}Copyright (c) 2024${NORMAL} Vasileios Filippos Skarleas & Yanis Sadoun - All rights reserved"
fi
