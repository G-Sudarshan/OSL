BOOK="address_book.txt"

# get details from user
echo -n "Enter the name of person: "
read name

echo -n "Enter the conact no. of person: "
read phone

# echo the answer and ask for confirmation

echo "Should I enter the values: "
echo -e "$name : $phone \n"
echo -n "y/n: "
read answer

if [ "$answer" = "y" ]
then 
    echo "$name : $phone" >> $BOOK
    echo "Contact saved successfully"
else
    echo "$name : $phone NOT saved to addressbook"
fi

exit 0
