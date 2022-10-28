(define (problem gripper_hard)
	(:domain gripper)

	(:objects
		rooma roomb roomc roomd roome
		ball1 ball2 ball3 ball4 ball5 ball6 ball7 ball8 ball9 ball10
		left right)

	(:init
		(ROOM rooma) (ROOM roomb) (ROOM roomc) (ROOM roomd) (ROOM roome)
		(BALL ball1) (BALL ball2) (BALL ball3) (BALL ball4) (BALL ball5)
        (BALL ball6) (BALL ball7) (BALL ball8) (BALL ball9) (BALL ball10)
		(GRIPPER left) (GRIPPER right) (free left) (free right)
		(at-robby rooma)
		(at-ball ball1 rooma) (at-ball ball2 rooma)
		(at-ball ball3 rooma) (at-ball ball4 rooma)
        (at-ball ball5 rooma) (at-ball ball6 rooma)
		(at-ball ball7 rooma) (at-ball ball8 rooma)
        (at-ball ball9 rooma) (at-ball ball10 rooma))

	(:goal
		(and (at-ball ball1 roomb)
		(at-ball ball2 roomb)
		(at-ball ball3 roomb)
		(at-ball ball4 roomb)
        (at-ball ball5 roomb)
        (at-ball ball6 roomb)
        (at-ball ball7 roomb)
        (at-ball ball8 roomb)
        (at-ball ball9 roomb)
        (at-ball ball10 roomb)))
)