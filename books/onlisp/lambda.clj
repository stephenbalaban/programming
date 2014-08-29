;;
;; Macros for a "light wrapping" on lambda calculus
;;

(defmacro λ [arg expr]
  `(fn* [~arg] ~expr))

(defn p [& args]
  (dotimes [i (count args)]
    (println (nth args i))))

(def id (λ x x))
(def self (λ s (s s)))
(def fst (λ x (λ y x)))
(def snd (λ x (λ y y)))

(def COND (λ p (λ a (λ b ((p a) b)))))
(def IF COND)

(def T fst)
(def F snd)
(def NIL F)

;; propositional logic
(def AND (λ a (λ b ((a b) F))))
(def OR (λ a (λ b ((a T) b))))
(def NOT (λ a ((a F) T)))
(def IMP (λ a (λ b ((a b) T))))

;; Note that IMP (logical implies or material implication) is equivalent to:
;;     (λ a (λ b (((IF a) b) T)))


;; Lists
;; head -> tail
(def CONS (λ h (λ t (λ s ((s h) t)))))

;; TODO implement list and nested function call macros
(def lst ((CONS 1)
            ((CONS 2)
               ((CONS 3)
                  ((CONS 4)
                     ((CONS 5) NIL))))))

(def head (λ l (l fst)))
(def tail (λ l (l snd)))

(def NIL? (λ t ((t F) T)))

(p (((COND T) "TRUE") "FALSE")
   (((COND F) "TRUE") "FALSE")
   (head lst)
   (head (tail lst))
   (head (tail (tail lst)))
   (head (tail (tail (tail lst))))
   (head (tail (tail (tail (tail lst)))))
   (head (tail (tail (tail (tail (tail lst))))))
   )

(def unbounded-recursion (λ x (self self)))
