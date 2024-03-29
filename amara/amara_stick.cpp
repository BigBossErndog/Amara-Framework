namespace Amara {
    int JOYSTICK_DEADZONE = 12000;

    class Stick: public Amara::Button {
        public:
            Sint16 xvalue = 0;
            Sint16 yvalue = 0;

            double angle = 0;

            bool xactive = false;
            bool yactive = false;

            Amara::Button* up;
            Amara::Button* down;
            Amara::Button* left;
            Amara::Button* right;

            Stick(Amara::Buttoncode bcode): Amara::Button(bcode) {
                up = new Amara::Button();
                down = new Amara::Button();
                left = new Amara::Button();
                right = new Amara::Button();
            }

            void pushX(Sint16 value) {
                if (value < -JOYSTICK_DEADZONE && xvalue > -JOYSTICK_DEADZONE) {
                    left->press();
                }
                else if (value > -JOYSTICK_DEADZONE && xvalue < -JOYSTICK_DEADZONE) {
                    left->release();
                }

                if (value > JOYSTICK_DEADZONE && xvalue < JOYSTICK_DEADZONE) {
                    right->press();
                }
                else if (value < JOYSTICK_DEADZONE && xvalue > JOYSTICK_DEADZONE) {
                    right->release();
                }

                if (left->isDown || right->isDown) xactive = true;

                xvalue = value;
            }

            void pushY(Sint16 value) {
                if (value < -JOYSTICK_DEADZONE && yvalue > -JOYSTICK_DEADZONE) {
                    up->press();
                }
                else if (value > -JOYSTICK_DEADZONE && yvalue < -JOYSTICK_DEADZONE) {
                    up->release();
                }

                if (value > JOYSTICK_DEADZONE && yvalue < JOYSTICK_DEADZONE) {
                    down->press();
                }
                else if (value < JOYSTICK_DEADZONE && yvalue > JOYSTICK_DEADZONE) {
                    down->release();
                }

                if (up->isDown || down->isDown) yactive = true;

                yvalue = value;
            }

			void manage() {
                xactive = false;
                yactive = false;

				Amara::Button::manage();
                up->manage();
                down->manage();
                left->manage();
                right->manage();
                
				angle = angleBetween(0, 0, xvalue, yvalue);
			}
    };
}