# How to run my test:

There is a run_test.sh file. 
Run it on you computer.

# Mac/Linux:
    Make sure your terminal is the same directory of run_test.sh
    
    Give execute permission to script:
        chmod +x run_test.sh
        
    Run the script:
        ./run_test.sh

# Special Description:
* Replace:
    When an entry with same key value is put in list. 
    The memory of old key will be dellocated, same as the old value. 
    
    To retrieve the value, you should use the new key.
    
* Remove:
    Remove function return the value, user needs to DELLOCATE IT by HIMSELF/HERSELF.
