function menu() {
  echo "Select any option: A B C D"
  read selection

  case "$selection" in
    A | a)
      echo "$(hostname)"
      echo "$(uptime)"
      ;;
    B | b)
      echo "Disk Usage:"
      df -h
      echo ""
      echo "Memory Usage:"
      ;;
    C | c)
      echo "Home Space Utilization:"
      du -h --max-depth=1 ~ | sort -hr
      ;;
    D | d)
      echo "Exiting program....."
      exit 0
      ;;
    *)
      echo "Try Try and Try again"
      ;;
  esac
}

menu
