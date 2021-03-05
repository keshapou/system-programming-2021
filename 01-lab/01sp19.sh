# red color
RED='\033[0;31m'

# no color
NC='\033[0m'

error()
{
  echo -ne "${RED}Error: $@${NC}\n" >&2
}

cancel() 
{
  echo -ne "\nCancelled.\n"
  exit 0
}

to_continue()
{
  printf "Do you want to continue? [y/n] : "
  read answer
  case "$answer" in
    [yY][eE][sS] | [yY] | "") 
      return 0
      ;;
    [nN][oO] | [nN]) 
      return 1
      ;;
    *) 
      return 2
  esac
}

check_pass()
{
  awk "/^$username/" /etc/shadow
}

input_user()
{
  read -p "Enter the user name: " username
  if ! id "$username" >/dev/null 2>&1; then
    error "this user doesn't exist"
    return 1
  fi

  return 0
}

menu()
{
  echo "
Options:
1) Lock - lock the password of the named account
2) Unlock - unlock the password of the named account
3) Check - check the password state
4) Exit - exit the programm
  "
  read -p "Select the option: " answer
  case "$answer" in
    "1")
      echo "Locking the password..."
      passwd "$username" -l
      ;;
    "2")
      echo "Unlocking the password..."
      passwd "$username" -u
      ;;
    "3")
        check_pass
        ;;  
    "4")
      echo "Bye."
      exit 0
      ;;
    *)
      error "invalid option."
  esac
}

trap cancel INT

echo "
Password Management
This script allows you to manage user passwords
made by liza swarovski (737-1)"

while true; do
  if input_user; then
    menu
  fi

  to_continue
  rc=$?
  if [ "$rc" = "1" ]; then
    echo "Bye."
    break
  elif [ "$rc" = "2" ]; then
    error "aborted."
    exit 1
  fi
done

exit 0
