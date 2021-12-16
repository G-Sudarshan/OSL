BOOK="address_book.txt"

exit=0

while [ $exit -ne 1 ]
do
    echo "what operation do you want to perform: "
    echo -e "add, display, search, delete, exit: "
    read answer

    if [ "$answer" = "add" ]
    then
        ./addcontact.sh
    elif [ "$answer" = "display" ]
    then
        ./displaycontact.sh
    elif [ "$answer" = "search" ]
    then 
        ./searchcontact.sh
    elif [ "$answer" = "delete" ]
    then 
        ./deletecontact.sh
    elif [ "$answer" = "exit" ]
    then
        exit=1
    else
        echo "Invalid option"
    fi

done
exit 0