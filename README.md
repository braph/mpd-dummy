# mpd-dummy

MPD dummy server that just displays a "Start MPD" entry.

Useful for stopping/starting the MPD inside ncmpcpp:

```
   ~/.ncmpcpp/bindings:
      def_key "S"
         stop
         run_external_command "killall mpd"
         run_external_command "mpdummy"
```
