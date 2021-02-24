# red color
RED='\033[0;31m'

# no color
NC='\033[0m'

error()
{
  echo -ne "${RED}Error: $@${NC}\n" >&2
}

ctrl_c() 
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

input_user()
{
  printf "Enter the user name: "
  read username
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
3) Exit - exit the programm
  "
  printf "Select the option: "
    read answer
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
        echo "Bye."
        exit 0
        ;;
      *)
        error "invalid option."
    esac
}

trap ctrl_c INT

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
