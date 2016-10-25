;;;; En tete pour script de test ;;;;;;;;;;
; TEST_RETURN_CODE=PASS
; TEST_COMMENT="evolved define"
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

(define unGrandSymbolePourStockerPasGrandChoseEtQuiEstUnPeuInutil (if #t 8 9)); unGrandSymbolePourStockerPasGrandChoseEtQuiEstUnPeuInutil
unGrandSymbolePourStockerPasGrandChoseEtQuiEstUnPeuInutil;8
(define y (define x 7) ) ; y
x ; 7
(define x (or #f "true")) ; x
x ; "true"
(define x (something wrong)) ; ()
x
