; TEST_RETURN_CODE=PASS
; TEST_COMMENT=fail_set!


(set! x 4)
(set!)
(set! 4)
(set! x)
(set! 5 5)
(set! 8 x)
(set! (or #t #f) 8)
