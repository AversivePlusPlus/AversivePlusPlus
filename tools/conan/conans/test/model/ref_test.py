import unittest
from conans.model.ref import ConanFileReference
from conans.errors import ConanException


class RefTest(unittest.TestCase):
    def basic_test(self):
        ref = ConanFileReference.loads("opencv/2.4.10 @ lasote/testing")
        self.assertEqual(ref.name, "opencv")
        self.assertEqual(ref.version, "2.4.10")
        self.assertEqual(ref.user, "lasote")
        self.assertEqual(ref.channel, "testing")
        self.assertEqual(str(ref), "opencv/2.4.10@lasote/testing")

        ref = ConanFileReference.loads("opencv_lite/2.4.10@phil-lewis/testing")
        self.assertEqual(ref.name, "opencv_lite")
        self.assertEqual(ref.version, "2.4.10")
        self.assertEqual(ref.user, "phil-lewis")
        self.assertEqual(ref.channel, "testing")
        self.assertEqual(str(ref), "opencv_lite/2.4.10@phil-lewis/testing")

    def errors_test(self):
        self.assertRaises(ConanException, ConanFileReference.loads, "")
        self.assertRaises(ConanException, ConanFileReference.loads, "opencv/2.4.10")
        self.assertRaises(ConanException, ConanFileReference.loads, "opencv/2.4.10 @ lasote")
        self.assertRaises(ConanException, ConanFileReference.loads, "opencv??/2.4.10@laso/testing")
        self.assertRaises(ConanException, ConanFileReference.loads, ".opencv/2.4.10@lasote/testing")
        self.assertRaises(ConanException, ConanFileReference.loads, "o/2.4.10 @ lasote/testing")
