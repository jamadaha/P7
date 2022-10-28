(define (domain gripper)
	(:requirements :strips :equality)

	(:predicates
		(ROOM ?x) (BALL ?x) (GRIPPER ?x)
		(at-robby ?x) (at-ball ?x ?y)
		(free ?x) (carry ?x ?y))

	(:action move
		:parameters (?x ?y)
		:precondition (and (ROOM ?x) (ROOM ?y) (not (= ?x ?y)) (at-robby ?x))
		:effect (and (at-robby ?y) (not (at-robby ?x))))

	(:action pick-up
		:parameters (?x ?y ?z)
		:precondition (and (BALL ?x) (ROOM ?y) (GRIPPER ?z) (at-ball ?x ?y) (at-robby ?y) (free ?z))
		:effect (and (carry ?z ?x) (not (at-ball ?x ?y)) (not (free ?z))))

	(:action drop
		:parameters (?x ?y ?z)
		:precondition (and (BALL ?x) (ROOM ?y) (GRIPPER ?z) (carry ?z ?x) (at-robby ?y))
		:effect       (and (at-ball ?x ?y) (free ?z) (not (carry ?z ?x))))
)




pick-up (b1, rooma, left) -> move (rooma, roomb)

(:action pick-up
	:parameters (b1 rooma left)
	:precondition (and (BALL b1) (ROOM rooma) (GRIPPER left) (at-ball b1 rooma) (at-robby rooma) (free left))
	:effect (and (carry left b1) (not (at-ball b1 rooma)) (not (free left))))

(:action move
	:parameters (rooma roomb)
	:precondition (and (ROOM rooma) (ROOM roomb) (not (= rooma roomb)) (at-robby rooma))
	:effect (and (at-robby roomb) (not (at-robby rooma))))

(:action macro1
	:parameters (b1 rooma left roomb)
	:precondition (and (BALL b1) (ROOM rooma) (GRIPPER left) (at-ball b1 rooma) (at-robby rooma) (free left)       (ROOM roomb) (at-robby rooma))
	:effect (and (at-robby roomb) (not (at-robby rooma)) (carry left b1) (not (at-ball b1 rooma)) (not (free left)))
	)

pick-up (b1, rooma, left) -> move (rooma, roomb) -> drop(b1, roomb, left) -> move (roomb, rooma)

(:action pick-up
	:parameters (b1 rooma left)
	:precondition (and (BALL b1) (ROOM rooma) (GRIPPER left) (at-ball b1 rooma) (at-robby rooma) (free left))
	:effect (and (carry left b1) (not (at-ball b1 rooma)) (not (free left))))

(:action move
		:parameters (rooma roomb)
		:precondition (and (ROOM rooma) (ROOM roomb) (not (= rooma roomb)) (at-robby rooma))
		:effect (and (at-robby roomb) (not (at-robby rooma))))

(:action macro2.1
	:parameters (b1 rooma left roomb)
	:precondition (and (BALL b1) (ROOM rooma) (GRIPPER left) (at-ball b1 rooma) (at-robby rooma) (free left) 
	(ROOM roomb) (at-robby rooma))
	:effect (and (at-robby roomb) (not (at-robby rooma)) (carry left b1) (not (at-ball b1 rooma)) (not (free left)))
	)

(:action drop
	:parameters (b1 roomb left)
	:precondition (and (BALL b1) (ROOM roomb) (GRIPPER left) (carry left b1) (at-robby roomb))
	:effect       (and (at-ball b1 roomb) (free left) (not (carry left b1))))

(:action marco2.2
	:parameters (b1 rooma left roomb)
	:precondition (and (BALL b1) (ROOM rooma) (GRIPPER left) (at-ball b1 rooma) (at-robby rooma) (free left) (ROOM roomb) (at-robby rooma)
	)
	:effect (and (at-ball b1 roomb) (not (carry left b1))
	(at-robby roomb) (not (at-robby rooma)) (not (at-ball b1 rooma))))

(:action move
	:parameters (roomb rooma)
	:precondition (and (ROOM roomb) (ROOM rooma) (not (= roomb rooma)) (at-robby roomb))
	:effect (and (at-robby rooma) (not (at-robby roomb))))

(:action macro2.3
	:parameters (b1 rooma left roomb)
	:precondition (and (BALL b1) (ROOM rooma) (GRIPPER left) (at-ball b1 rooma) (at-robby rooma) (free left) (ROOM roomb) (at-robby rooma)
	)
	:effect ((and (at-robby rooma)
	(at-ball b1 roomb) (not (carry left b1))))

)