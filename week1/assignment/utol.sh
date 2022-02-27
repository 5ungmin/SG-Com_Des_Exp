echo "working directory:"

read dirname

if [ -n "$dirname" ]
then
        cd $dirname
        if [ $? -ne 0 ]
        then
                echo "Failed: cannot cd $dirname."
                exit 1
        fi
else
        dirname=$pwd
fi

for file in *
do
        newname=`echo $file | tr "[a-z] [A-Z]" "[A-Z] [a-z]"`
        mv $file $newname
done

