function checkPalindrome() {
  echo "Enter a number: "
  read number

  originalNumber=$number
  reverseNumber=0

  while [ $number -gt 0 ]
  do
    remainder=$(( $number % 10 ))
    reverseNumber=$(( $reverseNumber * 10 + $remainder ))
    number=$(( $number / 10 ))
  done

  if [ $originalNumber -eq $reverseNumber ]
  then
    echo "Your number is a palindrome."
  else
    echo "Your number is not a palindrome."
  fi
}

checkPalindrome
