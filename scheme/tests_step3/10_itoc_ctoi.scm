;;;; En tete pour script de test ;;;;;;;;;;
; TEST_RETURN_CODE=PASS
; TEST_COMMENT="simple itoc ctoi"
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

(integer->char (char->integer #\( ))
(integer->char (char->integer #\] ))
(integer->char (char->integer #\[ ))
(integer->char (char->integer #\) ))
(integer->char (char->integer #\t ))
(integer->char (char->integer #\? ))
(integer->char (char->integer #\M ))
(integer->char (char->integer #\! ))
(integer->char (char->integer #\+ ))
(integer->char (char->integer #\- ))
(integer->char (char->integer #\/ ))
(integer->char (char->integer #\* ))
(integer->char (char->integer #\j ))
(integer->char (char->integer #\< ))
(char->integer (integer->char 37 ))
(char->integer (integer->char 97 ))
(char->integer (integer->char 122 ))
