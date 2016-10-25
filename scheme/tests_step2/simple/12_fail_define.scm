; TEST_RETURN_CODE=PASS
; TEST_COMMENT=fail_define

(define x 4)
(define)
(define 4)
(define x)
(define 5 5)
(define 8 x)
(define (or #t #f) 8)


