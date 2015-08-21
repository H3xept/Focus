# Focus
Temporary block websites and have a distraction free programming session.
##Info
This project is mostly an exercise, the code may be messy and bugs may come up.

# Usage
Actually you can only add new urls to the configuration file. 

##Add URLs

`./focus -a www.google.com google.com`

*To block a website you will usually have to insert the 'www' version and the 'www'-less version of the url.*
To confirm changes your browser needs to be restarted. 

**Be sure to exit the app by right-clicking it in the dock and hitting *quit*.**

##Delete URLs

Since the delete function is still in development, you will have to manually delete the entries from the hosts file. 

`sudo nano /etc/hosts` (Open file with nano editor)

*Delete entries...*

<kbd>Ctrl</kbd> + <kbd>O</kbd> (Write)

<kbd>Enter</kbd>

<kbd>Ctrl</kbd> + <kbd>X</kbd> (Exit)

