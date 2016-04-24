#pragma once

class SFMoveList
{
public:

	typedef deque< SFMove >::const_iterator			const_iterator;
	typedef deque< SFMove >::const_reverse_iterator	const_reverse_iterator;

	SFMoveList() :
		mLastMoveTimestamp(-1.f)
	{}

	const	SFMove&	AddMove(const SFInputState& inInputState, float inTimestamp);
	bool	AddMoveIfNew(const SFMove& inMove);

	void	RemovedProcessedMoves(float inLastMoveProcessedOnServerTimestamp);

	float			GetLastMoveTimestamp()	const { return mLastMoveTimestamp; }

	const SFMove&		GetLatestMove()			const { return mMoves.back(); }

	void			Clear() { mMoves.clear(); }
	bool			HasMoves()				const { return !mMoves.empty(); }
	int				GetMoveCount()			const { return mMoves.size(); }

	//for for each, we have to match stl calling convention
	const_iterator	begin()					const { return mMoves.begin(); }
	const_iterator	end()					const { return mMoves.end(); }

private:

	float			mLastMoveTimestamp;
	deque< SFMove >	mMoves;

};