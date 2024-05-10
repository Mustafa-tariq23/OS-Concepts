function arithmetic {
  echo "Enter Starting Number"
  read a1
  echo "How many numbers you want?"
  read n
  echo "Enter Increment"
  read d
  echo "The series is: "
  for((i = 0; i < n; i++))
  do
  temp=$(($i*$d))
  an=$(($a1+$temp))
  echo $an
  done
}
arithmetic