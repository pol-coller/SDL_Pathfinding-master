#include "Player.h"
using namespace std;

Player::Player() : sprite_texture(0),
position(Vector2D(100, 100)),
target(Vector2D(1000, 100)),
velocity(Vector2D(0, 0)),
currentTargetIndex(-1),
mass(0.1f),
max_force(150),
max_velocity(200),
orientation(0),
sprite_num_frames(0),
sprite_w(0),
sprite_h(0),
draw_sprite(false)
{
}

Player::~Player()
{
	if (sprite_texture)
		SDL_DestroyTexture(sprite_texture);
	if (steering_behaviour)
		delete (steering_behaviour);
}

void Player::setBehavior(SteeringBehavior* behavior)
{
	steering_behaviour = behavior;
}
void Player::setPathBehavior(Pathfinding* path)
{
	pathfinding = path;
}
Vector2D Player::getPosition()
{
	return position;
}

Vector2D Player::getTarget()
{
	return target;
}

Vector2D Player::getVelocity()
{
	return velocity;
}

float Player::getMaxVelocity()
{
	return max_velocity;
}

float Player::getMaxForce()
{
	return max_force;
}

float Player::getMass()
{
	return mass;
}

void Player::setPosition(Vector2D _position)
{
	position = _position;
}

void Player::setTarget(Vector2D _target)
{
	target = _target;
}

void Player::setVelocity(Vector2D _velocity)
{
	velocity = _velocity;
}

void Player::update(float dtime, SDL_Event* event)
{

	//cout << "agent update:" << endl;

	switch (event->type) {
		/* Keyboard & Mouse events */
	case SDL_KEYDOWN:
		if (event->key.keysym.scancode == SDL_SCANCODE_SPACE)
			draw_sprite = !draw_sprite;
		break;
	default:
		break;
	}

	// Apply the steering behavior
	steering_behaviour->applySteeringForce(this, dtime);

	// Update orientation
	if (velocity.Length())
		orientation = (float)(atan2(velocity.y, velocity.x) * RAD2DEG);

	// Trim position values to window size
	if (position.x < 0) position.x = TheApp::Instance()->getWinSize().x;
	if (position.y < 0) position.y = TheApp::Instance()->getWinSize().y;
	if (position.x > TheApp::Instance()->getWinSize().x) position.x = 0;
	if (position.y > TheApp::Instance()->getWinSize().y) position.y = 0;
}


void Player::addPathPoint(Vector2D point)
{
	if (path.points.size() > 0)
		if (path.points[path.points.size() - 1] == point)
			return;

	path.points.push_back(point);
}


int Player::getCurrentTargetIndex()
{
	return currentTargetIndex;
}

int Player::getPathSize()
{
	return path.points.size();
}

Vector2D Player::getPathPoint(int idx)
{
	return path.points[idx];
}

void Player::clearPath()
{
	setCurrentTargetIndex(-1);
	path.points.clear();
}

void Player::setCurrentTargetIndex(int idx)
{
	currentTargetIndex = idx;
}

void Player::draw()
{
	// Path
	for (int i = 0; i < (int)path.points.size(); i++)
	{
		draw_circle(TheApp::Instance()->getRenderer(), (int)(path.points[i].x), (int)(path.points[i].y), 15, 255, 255, 0, 255);
		if (i > 0)
			SDL_RenderDrawLine(TheApp::Instance()->getRenderer(), (int)(path.points[i - 1].x), (int)(path.points[i - 1].y), (int)(path.points[i].x), (int)(path.points[i].y));
	}

	if (draw_sprite)
	{
		Uint32 sprite;

		if (velocity.Length() < 5.0)
			sprite = 1;
		else
			sprite = (int)(SDL_GetTicks() / (-0.1 * velocity.Length() + 250)) % sprite_num_frames;

		SDL_Rect srcrect = { (int)sprite * sprite_w, 0, sprite_w, sprite_h };
		SDL_Rect dstrect = { (int)position.x - (sprite_w / 2), (int)position.y - (sprite_h / 2), sprite_w, sprite_h };
		SDL_Point center = { sprite_w / 2, sprite_h / 2 };
		SDL_RenderCopyEx(TheApp::Instance()->getRenderer(), sprite_texture, &srcrect, &dstrect, orientation + 90, &center, SDL_FLIP_NONE);
	}
	else
	{
		draw_circle(TheApp::Instance()->getRenderer(), (int)position.x, (int)position.y, 15, 255, 255, 255, 255);
		SDL_RenderDrawLine(TheApp::Instance()->getRenderer(), (int)position.x, (int)position.y, (int)(position.x + 15 * cos(orientation * DEG2RAD)), (int)(position.y + 15 * sin(orientation * DEG2RAD)));
	}


}

bool Player::loadSpriteTexture(char* filename, int _num_frames)
{
	if (_num_frames < 1) return false;

	SDL_Surface* image = IMG_Load(filename);
	if (!image) {
		cout << "IMG_Load: " << IMG_GetError() << endl;
		return false;
	}
	sprite_texture = SDL_CreateTextureFromSurface(TheApp::Instance()->getRenderer(), image);

	sprite_num_frames = _num_frames;
	sprite_w = image->w / sprite_num_frames;
	sprite_h = image->h;
	draw_sprite = true;

	if (image)
		SDL_FreeSurface(image);

	return true;
}